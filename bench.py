import sys
import os
import os.path
import subprocess
import shutil
import ast

from datetime import datetime
import pickle 


# settings
###########################################################################

VERBOSE = False
VERBOSE_BENCH = False
INPUT_IMAGE = "bhudda_1080p.png"

#test algorithm parameters
S = 50
R = 0.5
N = 3

# bench settings
BENCH_PARAMS = [
    # dict(S=50,R=0.5,N=3,IMG='bhudda_200.png'),
    # dict(S=50,R=0.5,N=3,IMG='bhudda_320.png'),
    # dict(S=50,R=0.5,N=3,IMG='bhudda_640.png'),
    dict(S=50,R=0.5,N=3,IMG='bhudda_1080p.png'),
    # dict(S=50,R=0.5,N=3,IMG='bhudda_2048.png'),
    # dict(S=50,R=0.5,N=3,IMG='bhudda_4k.png'),
    # dict(S=50,R=0.9,N=3),
    # dict(S=50,R=1.4,N=3),
]

# benchmark iterations
T = 10 

#ignore these implementations
IGNORE = [
    #'00_simple_transpose',
    '01_blocked_transpose',
    '02_inl_filter_bounds',
    '03a_inl_row_sat',
    '03b_recombination',
    '04a_alt_inl_row_sat',
    '05_merged',
    'current1',
    'current20_20',
    'current40_40',
    '07_uchar3',
    '07_uchar3_2',
    'uchar3_invD',
    '07b_invD',
    'hmm'
    #'06_write_transposed',
    # 'current',
]

# globals
###########################################################################

SCRIPT_PATH = ""
IMPL_PATH = ""

# util
###########################################################################

def printSeparator():
    print "-------------------------------------------------"

def compile(impl):
    sconsPath = os.path.join(SCRIPT_PATH,'implementations')
    cmd = ['scons','-C',sconsPath,'--variant='+impl]
    output = subprocess.check_output(cmd)
    if VERBOSE:
        print output
        printSeparator()

def clean(impl):
    sconsPath = os.path.join(SCRIPT_PATH,'implementations')
    cmd = ['scons','-C',sconsPath,'--variant='+impl, '-c']
    output = subprocess.check_output(cmd)
    if VERBOSE:
        print output
        printSeparator()

def run(impl, inputImg, outputImg, s, r, n):
    ex = os.path.join(IMPL_PATH,impl,'bin',"DomainTransform")
    cmd = [ex,
        '-m','nc',
        '-i',inputImg,
        '-o',outputImg,
        '-s',str(s),
        '-r',str(r),
        '-n',str(n),
    ]

    output = subprocess.check_output(cmd);
    if VERBOSE:
        print output
        printSeparator()

def bench(impl, inputImg, s,r,n,t):
    ex = os.path.join(IMPL_PATH,impl,'bin',"DomainTransform")
    cmd = [ex,
        '-m','nc',
        '-i',inputImg,
        '-s',str(s),
        '-r',str(r),
        '-n',str(n),
        '-b',
        '-t',str(t),
    ]

    output = subprocess.check_output(cmd);
    if VERBOSE_BENCH:
        print output
        printSeparator()
    result = ast.literal_eval(output)
    return result


# Find all implementation folders
###########################################################################

SCRIPT_PATH = os.path.dirname(os.path.realpath(__file__))
IMPL_PATH = os.path.join(SCRIPT_PATH,"implementations")

folders = [o for o in os.listdir(IMPL_PATH) if os.path.isdir(os.path.join(IMPL_PATH,o))]

folders = [f for f in folders if not f in IGNORE]

# run
###########################################################################

#remove old output
outFolderPath = os.path.join(SCRIPT_PATH,'output')
shutil.rmtree(outFolderPath,ignore_errors=True)
os.makedirs(outFolderPath)

printSeparator()

# run measurements
results = {}
for f in folders:
    p = os.path.join(IMPL_PATH,f)
    print f
    printSeparator()

    clean(f)

    compile(f)

    relativePath = os.path.join(IMPL_PATH,f,'bin')
    outPath = os.path.join(SCRIPT_PATH,"output",f+'.'+INPUT_IMAGE)
    inPath = os.path.join(SCRIPT_PATH,'images',INPUT_IMAGE)
    run(f,inPath,outPath,s=S,r=R,n=N)

    variantResults = []
    for bp in BENCH_PARAMS:
        inImg = os.path.join(SCRIPT_PATH,'images',bp['IMG'])
        result = bench(f,inImg,s=bp['S'],r=bp['R'],n=bp['N'],t=T)
        variantResults.append(result)
    results[f] = variantResults

# save results
benchFolderPath = os.path.join(SCRIPT_PATH,'bench_results')
if not os.path.exists(benchFolderPath):
    os.makedirs(benchFolderPath)
benchFile = "data_"+datetime.now().strftime('%y_%m_%d__%H_%M')+'.pickle'
benchDataPath = os.path.join(SCRIPT_PATH,'bench_results',benchFile)
pickle.dump(results, open(benchDataPath, 'wb'))

# some simple analysis
###########################################################################
print "Analysis"
printSeparator()
for (i,bp) in enumerate(BENCH_PARAMS):
    print bp
    printSeparator()
    tmp = []
    for (variant,data) in results.iteritems():
        cycles = data[i]['total_cycles'] / data[i]['benchmark_iterations']
        w = data[i]['width']
        h = data[i]['height']
        cycles_per_pixel = cycles / (w*h)
        bf = data[i]['runtime_data'][-1]['cycles_call'] / (w*h)
        tmp.append( (cycles, variant,cycles_per_pixel,bf) )

    tmp.sort(key= lambda x: x[0])
    for t in tmp:
        print "{0:12} {1:>15.3f}%  {2:>12.1f}    {3:>12.1f}    {4:<40}".format(t[0],100*t[0]/tmp[-1][0],t[2],t[3],t[1])

    printSeparator()


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

VERBOSE = True
VERBOSE_BENCH = False
INPUT_IMAGE = "kyoto_1080p.png"

#test algorithm parameters
S = 50
R = 0.5
N = 3

# bench settings
BENCH_PARAMS = [
    dict(S=50,R=0.5,N=3),
    dict(S=50,R=0.9,N=3),
    dict(S=50,R=1.4,N=3),
]

# benchmark iterations
T = 10 

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
    result = ast.literal_eval(output)
    if VERBOSE_BENCH:
        print result
        printSeparator()
    return result


# Find all implementation folders
###########################################################################

SCRIPT_PATH = os.path.dirname(os.path.realpath(__file__))
IMPL_PATH = os.path.join(SCRIPT_PATH,"implementations")

folders = [o for o in os.listdir(IMPL_PATH) if os.path.isdir(os.path.join(IMPL_PATH,o))]

folders = [f for f in folders if not f.startswith('_')]

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
        result = bench(f,inPath,s=bp['S'],r=bp['R'],n=bp['N'],t=T)
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
        tmp.append( (cycles, variant) )

    tmp.sort(key= lambda x: x[0])
    for t in tmp:
        print "{0:12} {1:>15.3f}%    {2:<40}".format(t[0],t[0]/tmp[-1][0],t[1])

    printSeparator()


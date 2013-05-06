import sys
import os
import os.path
import pickle


# plotting
#####################################

def plot(dataPath,pdfPath):
	# prepare data
	pass

# running
#####################################

SCRIPT_PATH = os.path.dirname(os.path.realpath(__file__))
BENCH_PATH = os.path.join(SCRIPT_PATH,"bench_results")

files = [o for o in os.listdir(BENCH_PATH) if o.endswith('.pickle')]

for f in files:
	dataPath = os.path.join(BENCH_PATH,f)
	pdfPath = os.path.join(BENCH_PATH,f+'.pdf')
	if not os.path.exists(pdfPath):
		print dataPath
		plot(dataPath,pdfPath)




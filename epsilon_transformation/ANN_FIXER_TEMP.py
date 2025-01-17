INPUT_FILE = 'circus_gen/AnglePIDANN_Circus_17012025_163518.thy'
OUTPUT_FILE = 'output.thy'


def readFile():
	f = open(INPUT_FILE, 'r') 
	L = f.readlines()
	for i in range(len(L)):
		if(L[i].startswith('"HiddenLayer')):
			L[i] = L[i].replace("layerRes", "layerRes.(l-1)")
			print(L[i])
		if(L[i].startswith('"OutputLayer')):
			L[i] = L[i].replace("layerRes", "layerRes.(#inRanges-1)")
			print(L[i])
		if(L[i].startswith('"ANN')):
			L[i+1] = L[i+1].replace("layerRes", "layerRes.(#inRanges-1)")
			print(L[i+1])
	writeToFile(L)
	
def writeToFile(L): 
	f = open(OUTPUT_FILE, 'w')
	f.writelines(L)
	f.close()

readFile()

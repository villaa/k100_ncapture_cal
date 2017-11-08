"""various functions to help deal with text data in Python """
def getXYdata_wYerr(infile=None):

  #format expected is (whitespace separated):
  #x	y	yerr

  #open the file return a dictionary with se,sw,nw,ne elements
  f = open(infile)

  #make a list for vector identifier 
  #first two are x-y of histogram-type step function
  #second two are a sort-of smooth curve to represent the function
  vecs = ['xx','yy','ey']

  #make a dictionary to store the pulses
  funcs = {}

  #read file N times, is this efficient?
  funcs[vecs[0]] = [x.split()[0] for x in f.readlines()]
  f.seek(0)
  funcs[vecs[1]] = [x.split()[1] for x in f.readlines()]
  f.seek(0)
  funcs[vecs[2]] = [x.split()[2] for x in f.readlines()]

  f.close()

  #convert to floats
  funcs[vecs[0]] = [float(i) for i in funcs[vecs[0]]]
  funcs[vecs[1]] = [float(i) for i in funcs[vecs[1]]]
  funcs[vecs[2]] = [float(i) for i in funcs[vecs[2]]]

  return funcs 


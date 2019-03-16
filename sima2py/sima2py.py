#!/usr/bin/env python

import numpy as np
import re
import os
#===============to suppress h5py warning see:
#https://github.com/h5py/h5py/issues/961
import warnings
warnings.simplefilter(action='ignore', category=FutureWarning)
import h5py
warnings.resetwarnings()
import argparse
from argparse import ArgumentParser, ArgumentTypeError
# Author: A. Villano
# The purpose here is to convert a Geant4 output text file
# to an h5 file with a workable output structure.
#
######################classes##############################
class simData:
	def __init__(self):
	  self.nhit = None 
	  self.NRhit = None 
	  self.ERhit = None 
	  self.NRedep = None 
	  self.ERedep = None
	  self.CapEvent = None

	#def __Print__(self):
	#  print 'self.nhit = %s' % str(self.nhit)

######################functions############################
def listFiles(path='./',regex=re.compile(r'(.*?)')):

        f = []
        for (dirpath, dirnames, filenames) in os.walk(path):
            passfiles = []
            for i,file in enumerate(filenames):
              if(regex.search(file) is not None):
                passfiles.extend([file])
            f.extend(passfiles)
            break

        f.sort()
        print(f)
        return dirpath,f 

def readFile(filename):

        f = open(filename)

        #assume the first line is the tags
        tags = f.readline().split()
        data = [x.split() for x in f.readlines()] 
        
        #convert to numpy array
        data = np.asarray(data,dtype=np.float64)

        #hard-code a cut?
        if np.shape(data)[0]>0:
          cHVDet = np.zeros(np.shape(data)[0],dtype=bool)
          cZeroEdep = np.zeros(np.shape(data)[0],dtype=bool)
          cNeutron = np.zeros(np.shape(data)[0],dtype=bool)
          cGamma = np.zeros(np.shape(data)[0],dtype=bool)
          cNR = np.zeros(np.shape(data)[0],dtype=bool)

          cHVDet[data[:,1]==1] = True
          cZeroEdep[data[:,6]==0] = True
          cNeutron[data[:,4]==2112] = True
          cGamma[data[:,4]==22] = True
          cNR[data[:,4]>3000] = True
          data = data[cHVDet&~cZeroEdep&cNR,:]

        f.close()
        return data,tags 

def readFiles(flist,dirpath='./'):

        d = []
        data,tags = readFile(dirpath+flist[0]) #FIXME bug in simcode only puts correct header for file 0 -- eventually need to check if n colums is same for all files and return error if not
        for n,f in enumerate(flist):
          print('{} ({} out of {})'.format(dirpath+f,n,np.shape(flist)[0]))
          data,t = readFile(dirpath+f)
          d.extend(data)

        #convert to numpy array
        d = np.asarray(d,dtype=np.float64)

        return d,tags 

def saveh5(ofile='data.h5',path='./',regex=re.compile(r'(.*?)')):

        #get the data
        dirpath, f = listFiles(path,regex)
        d, tags = readFiles(f,dirpath)

        #open and write file
        of = h5py.File(ofile, 'w')

        #hits dataset
        dset_hits = of.create_dataset("geant4/hits", np.shape(d), dtype=np.dtype('float64').type, compression="gzip", compression_opts=9)
        dset_hits[...] = d      

        of.close()
        return

#the stuff below is so this functionality can be used as a script
########################################################################
if __name__ == "__main__":

        #make a parser for the input
        parser = argparse.ArgumentParser(description='Input processing specifications')
        parser.add_argument('-d','--filedir', type=str, dest='filedir', default='./', help='directory to look for files')
        parser.add_argument('-x','--regex', type=str, dest='regstr', default=r'(.*?)', help='regex for picking up files')
        parser.add_argument('-o','--outfile', type=str, dest='outfile', default='data.h5', help='output file for data')
        #parser.set_defaults(filedir='./');

        args = parser.parse_args()

        try:
          #v = getPosition(args.iteration[0],args.n,pit) 

          print(args.filedir)
          print(args.regstr)
          print(args.outfile)
          saveh5(args.outfile,args.filedir,re.compile(args.regstr))
        except KeyboardInterrupt:
          print('Shutdown requested .... exiting')
        except Exception:
          traceback.print_exc(file=sys.stderr)



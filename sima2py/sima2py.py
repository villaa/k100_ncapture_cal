#!/usr/bin/env python

import warnings
warnings.simplefilter(action='ignore', category=FutureWarning)
import numpy as np
import pandas as pd
warnings.resetwarnings()
import re
import os
#===============to suppress h5py warning see:
#https://github.com/h5py/h5py/issues/961
#import warnings
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

#Is this list of lists rectangular?
def isRect(n):
        return all(len(i)==len(n[0]) for i in n)

def readFile(filename,cuts=None):

        f = open(filename)

        #assume the first line is the tags
        tags = f.readline().split()
        data = [x.split() for x in f.readlines()] 
       
        #Make sure all lines are complete
        if not isRect(data):
          print('Incomplete lines. Skipping file: '+filename)
          tags=[]
          data=[]

        #convert to numpy array
        data = np.asarray(data,dtype=np.float64)

        #hard-code a cut?
        if np.shape(data)[0]>0:
          cHVDet = np.zeros(np.shape(data)[0],dtype=bool)
          cLowE = np.zeros(np.shape(data)[0],dtype=bool)
          cCapture = np.zeros(np.shape(data)[0],dtype=bool)
          cZeroEdep = np.zeros(np.shape(data)[0],dtype=bool)
          cNeutron = np.zeros(np.shape(data)[0],dtype=bool)
          cGamma = np.zeros(np.shape(data)[0],dtype=bool)
          cNR = np.zeros(np.shape(data)[0],dtype=bool)
          cER = np.zeros(np.shape(data)[0],dtype=bool)

          cHVDet[data[:,1]==1] = True
          cLowE[data[:,6]<=0.01] = True #each hit less than 10 keV
          cCapture[data[:,21]==1] = True
          cZeroEdep[data[:,6]==0] = True
          cNeutron[data[:,4]==2112] = True
          cGamma[data[:,4]==22] = True
          cNR[data[:,4]>3000] = True
          cER[(data[:,4]==11)|(data[:,4]==-11)|(data[:,4]==22)] = True

          #event-level cuts
          #try to label events with consecutive and unique labels
          ev = data[:,0]

          #diffs = np.append(np.diff(ev),1)
          diffs = np.append(0,np.diff(ev))
          #diff_divide = np.copy(diffs)
          #diff_divide[diff_divide==0] = 1 #replace some elements with unity
          #diffs = diffs/diff_divide

          newev = np.cumsum(diffs)
          #now some event-level cuts
          evWithCapture = newev[cHVDet&cCapture]
          cWithCapture = np.isin(newev,evWithCapture)
          evWithHighE = newev[cHVDet&~cLowE]
          cWithHighE = np.isin(newev,evWithHighE)
          #checks for file: Run68_gdirect_bknd_R68_PuBe_0x0006_10M_1550295336_000_000.txt
          #print(cWithHighE[ev==775483])
          #print(cWithCapture[ev==5812160])

          if cuts=='NR':
            data = data[cHVDet&~cZeroEdep&cNR&~cWithCapture,:]
          elif cuts=='ER':
            data = data[cHVDet&~cZeroEdep&cER&~cWithHighE&~cWithCapture,:]
          elif cuts=='NRc':
            data = data[cHVDet&~cZeroEdep&cNR&cWithCapture,:]
          elif cuts=='Cap':
            data = data[cHVDet&cNeutron&cCapture,:]
          elif cuts=='wCap':
            data=data[cHVDet&cWithCapture,:]

        f.close()
        return data,tags 

def readFiles(flist,dirpath='./',cuts=None):

        d = []
        data,tags = readFile(dirpath+flist[0]) #FIXME bug in simcode only puts correct header for file 0 -- eventually need to check if n colums is same for all files and return error if not
        for n,f in enumerate(flist):
          print('{} ({} out of {})'.format(dirpath+f,n,np.shape(flist)[0]),flush=True)
          data,t = readFile(dirpath+f,cuts)
          d.extend(data)

        #convert to numpy array
        d = np.asarray(d,dtype=np.float64)

        return d,tags 

def saveh5(ofile='data.h5',path='./',regex=re.compile(r'(.*?)'),cuts=None,trimvec=[]):

        #get the data
        dirpath, f = listFiles(path,regex)
        d, tags = readFiles(f,dirpath,cuts)
        goodtags = list(set(tags) - set(trimvec))
        sel=np.sort([tags.index(i) for i in goodtags])
        tags = [tags[i] for i in sel]
        d = d[:,sel]

        #open and write file
        of = h5py.File(ofile, 'w')

        #hits dataset
        dset_hits = of.create_dataset("geant4/hits", np.shape(d), dtype=np.dtype('float64').type, compression="gzip", compression_opts=9)
        dset_hits[...] = d      

        of.close()
        return

#FIXME not yet used, should eventually be a more elegant way to do generalized cuts
def applyCuts(data=[],cutstring='',length=13):

    data_out = np.zeros((0,length))
    if np.shape(data)[0]>0:
      #hit-level cuts
      cHVDet = np.zeros(np.shape(data)[0],dtype=bool)
      cCapture = np.zeros(np.shape(data)[0],dtype=bool)
      cZeroEdep = np.zeros(np.shape(data)[0],dtype=bool)
      cNeutron = np.zeros(np.shape(data)[0],dtype=bool)
      cGamma = np.zeros(np.shape(data)[0],dtype=bool)
      cNR = np.zeros(np.shape(data)[0],dtype=bool)
      cER = np.zeros(np.shape(data)[0],dtype=bool)

      cHVDet[data[:,1]==1] = True
      cCapture[data[:,21]==1] = True
      cZeroEdep[data[:,6]==0] = True
      cNeutron[data[:,4]==2112] = True
      cGamma[data[:,4]==22] = True
      cNR[data[:,4]>3000] = True
      cER[(data[:,4]==11)|(data[:,4]==-11)|(data[:,4]==22)] = True

      #event-level cuts
      #try to label events with consecutive and unique labels
      ev = data[:,0]

      diffs = np.append(np.diff(ev),1)
      diff_divide = np.copy(diffs)
      diff_divide[diff_divide==0] = 1 #replace some elements with unity
      diffs = diffs/diff_divide

      newev = np.cumsum(diffs)
      #now some event-level cuts
      evWithCapture = newev[cCapture]
      cWithCapture = np.isin(newev,evWithCapture)

      #data = data[cHVDet&~cZeroEdep&cNR&~cWithCapture,:]
      data = data[cHVDet&~cZeroEdep&cER&~cWithCapture,:]

      reduced_data = data[:,[0,4,5,6,21]]
      #print(reduced_data)
      df = pd.DataFrame(data=reduced_data)
      groupbyvec=[0]

      #evec = np.zeros((0,length))
      nhit = np.zeros((0,1))

      for i in df.groupby(groupbyvec,axis=0)[3].apply(list):
        vector = np.zeros((1,length))
        #vector[0,0:np.shape(i)[0]] = np.transpose(np.asarray(i))
        arr = np.asarray(i)
        ue = np.minimum(length,np.shape(arr)[0]) #useful elements
        vector[0,0:ue] = arr[0:ue]
        data_out = np.append(data_out,vector*1e6,0) #convert from MeV
        nhit = np.append(nhit,np.shape(i)[0])

    return data_out

#the stuff below is so this functionality can be used as a script
########################################################################
if __name__ == "__main__":

        #make a parser for the input
        parser = argparse.ArgumentParser(description='Input processing specifications')
        parser.add_argument('-d','--filedir', type=str, dest='filedir', default='./', help='directory to look for files')
        parser.add_argument('-x','--regex', type=str, dest='regstr', default=r'(.*?)', help='regex for picking up files')
        parser.add_argument('-o','--outfile', type=str, dest='outfile', default='data.h5', help='output file for data')
        parser.add_argument('-c','--cuts', type=str, dest='cuts', default='NR', help='kind of cuts to apply')
        parser.add_argument('-t','--trimvec',nargs='*', type=str, dest='trimvec', default=[], help='parameters to remove from output')
        #parser.set_defaults(filedir='./');

        args = parser.parse_args()

        try:
          #v = getPosition(args.iteration[0],args.n,pit) 

          print(args.filedir)
          print(args.regstr)
          print(args.outfile)
          print(args.cuts)
          print(args.trimvec)
          saveh5(args.outfile,args.filedir,re.compile(args.regstr),args.cuts,args.trimvec)
        except KeyboardInterrupt:
          print('Shutdown requested .... exiting')
        except Exception:
          traceback.print_exc(file=sys.stderr)



#here we give functions to simplify the loading of Pu/Be source position scanning data

import numpy as np
import dataPython as dp
import scipy as sp
from scipy.stats import poisson


def getScanData(file='data/Run66Sim_FluxScan0.txt',Sig=0.0955): #assume total Ge cross sect

  #a function to get three rows of data x y z
  data = dp.getXYZdata(file)
  
  #turn into np array
  data['xx'] = np.array(data['xx'])
  data['yy'] = np.array(data['yy'])
  data['zz'] = np.array(data['zz'])
  
  #include sqrt(N) error
  data['ey'] = np.sqrt(data['yy'])
  data['eyl'],data['eyu'] = sp.stats.poisson.interval(0.68, data['yy'])
  data['eyl'] = np.abs(data['yy']-data['eyl'])
  data['eyu'] = np.abs(data['yy']-data['eyu'])
  
  
  #add in the factors for neutron flux V=258.5 cm^3; Sig=0.0955 cm^-1; nPrim=1e6; Source R=1.96e6 neut/s
  V=258.50
  #Sig=0.0955
  data['nPrim']=data['zz']*1e6
  SrcR=1.96e6
  
  nPrim = data['nPrim']
  data['yy'] = data['yy']*(SrcR/nPrim)*(1/(V*Sig))
  data['ey'] = data['ey']*(SrcR/nPrim)*(1/(V*Sig))
  data['eyl'] = data['eyl']*(SrcR/nPrim)*(1/(V*Sig))
  data['eyu'] = data['eyu']*(SrcR/nPrim)*(1/(V*Sig))

  return data

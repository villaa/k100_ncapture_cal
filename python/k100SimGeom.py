#here we give functions to simplify the organization of geometrical data from k100Sim 

import numpy as np


def getShieldPositions(): 

  #make an object to store things
  data = {} 

  #floor coordinate
  floorZ = -957.942/10.0 #units all cm
  
  #record positions
  data['westpoly'] = {} 
  data['westpoly']['yc'] = (29.0 - 12)*2.54
  data['westpoly']['yw'] = 8.0*2.54

  data['PuBeLead'] = {} 
  data['PuBeLead']['yc'] = (73.6 - 19.75 -16.0 -0.5*16.0 -2.25)*2.54 +0.5*27.5 #sorry for mixed units
  data['PuBeLead']['yw'] = 12.0*2.54
  
  data['PuBeBarrel'] = {} 
  data['PuBeBarrel']['yc'] = (73.6 -19.75 -16.0 -0.5*16.0 -2.25 +0.5*12 + 0.5*16.25)*2.54 +0.5*27.5 #sorry for mixed units
  data['PuBeBarrel']['yw'] = 16.25*2.54

  data['pit'] = {} 
  data['pit']['zc'] = np.abs(floorZ) + 0.5*6*12*2.54
  data['pit']['zw'] = 6*12*2.54 #6 feet

  return data


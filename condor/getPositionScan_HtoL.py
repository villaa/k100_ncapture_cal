#!/usr/bin/env python

import numpy as np
import argparse
from argparse import ArgumentParser, ArgumentTypeError
# Author: A. Villano
# The purpose here is to return a space-separated x y z tuple that
# represents the position of the Pu/Be source interpolating between the 
# high flux and low flux positions.
#

######################functions############################
def getPosition(iteration=1,n=10,pit=False):
	#first we need the endpoints -- label 'h' for high flux
	xh = 0 #cm
	yh = 33.02 #N-MISC-17-003 pg 29, #trelloP1
	zh = 0 #should be near detector height

        #modify for pit possibility
	if(pit):
	  yh = 0
	  zh = -60

	p_h = np.asarray([xh,yh,zh],dtype=np.float64)

	#see the file templates/Run66Shield_stdLocation_inBarrel.mac.template for the standard position point--label
	#'l' for low flux
	xl = 0 #cm
	yl = 119.731
	zl = -64.679

        #modify for pit possibility
	if(pit):
	  yl = 0
	  zl = -200

	p_l = np.asarray([xl,yl,zl],dtype=np.float64)

	#get unit vector pointing from high flux to low flux
	ltot = np.linalg.norm(p_l-p_h)
	uvec = (p_l-p_h)/ltot

	#chop up the region
	posvec = []
	N = n-1 
	for i in np.arange(N+1):
          d = ltot/np.float(N)
          vec = p_h + i*d*uvec
          if i==(iteration-1):
            posvec = vec

	return posvec

#the stuff below is so this functionality can be used as a script
########################################################################
if __name__ == "__main__":

        #make a parser for the input
        parser = argparse.ArgumentParser(description='Input processing specifications')
        parser.add_argument('-n','--n', type=int, dest='n', default=10, help='number of points, default 10')
        parser.add_argument("-r", "--radial", action="count", default=0)
        parser.add_argument("-p", "--pit", action="count", default=0)
        parser.add_argument('iteration', metavar='N', type=int, nargs='+', \
			                    help='iteration for the function cannot be larger than n')
        parser.set_defaults(n=10);
        parser.set_defaults(radial=0);
        parser.set_defaults(pit=0);

        args = parser.parse_args()

        radial = False #use a flag
        if args.radial>0:
          radial=True

        pit = False #use a flag
        if args.pit>0:
          pit=True

        try:
          v = getPosition(args.iteration[0],args.n,pit) 

          if (radial):
            print('{0:3.3f}'.format(np.linalg.norm(v))) 
          else:
            print('{0:3.2f}\t{1:3.2f}\t{2:3.2f}'.format(v[0],v[1],v[2])) 

        except KeyboardInterrupt:
          print('Shutdown requested .... exiting')
        except Exception:
          traceback.print_exc(file=sys.stderr)



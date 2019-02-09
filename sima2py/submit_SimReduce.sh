#!/bin/sh

#standard R66 config, neutrons from PuBe 
#scan "high-flux" to "low-flux" situation along straight line 
#for i in FluxScan4 FluxScan7 RateMeasure4 
for i in FluxScan7 
do
  sed -e 's|TAG|'${i}'|g' < condor-k100SimReduce > .condor
  condor_submit .condor
  rm .condor
done

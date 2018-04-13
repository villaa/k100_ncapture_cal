#!/bin/sh

#standard R66 config, neutrons from PuBe 
#scan "high-flux" to "low-flux" situation along straight line 
COUNTER=0
TAG=$1
for i in 1 2 3 4 5 6 7 8 9 10 
do
  #TAG='FluxScan4'
  DATASETIDHEX=`printf "0x%04x" ${COUNTER}`
  ARGS='--filedir=/data/chocula/villaa/k100Sim_Data/captureCal/ --regex='Run66Shield${TAG}_PuBe_${DATASETIDHEX}_1M\\S+' --outfile='/data/chocula/villaa/k100Sim_Data/captureCalhdf5/${TAG}_${DATASETIDHEX}.h5''
  ./sima2py.py ${ARGS}
  let COUNTER++
done

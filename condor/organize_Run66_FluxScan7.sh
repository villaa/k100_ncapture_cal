#!/bin/sh

#standard R66 config, neutrons from PuBe 
#scan "high-flux" to "low-flux" situation along straight line 
COUNTER=0
for i in 1 2 3 4 5 6 7 8 9 10
do
  DATASETIDHEX=`printf "0x%04x" ${COUNTER}`
  rad=`./getPositionScan_HtoL.py -r ${i}`
  num=`ls -lh /data/chocula/villaa/k100Sim_Data/captureCal/Run66ShieldFluxScan7_PuBe_${DATASETIDHEX}_1M*000.txt |awk 'END{print NR;}'`
  cat /data/chocula/villaa/k100Sim_Data/captureCal/Run66ShieldFluxScan7_PuBe_${DATASETIDHEX}_1M* |awk '{if($22==1 && $2==1){print $1"\t"$2"\t"$22}}' |awk -v rad=${rad} -v offset=${i} -v num=${num} 'END{print rad"\t"NR"\t"num}'
  let COUNTER++
done

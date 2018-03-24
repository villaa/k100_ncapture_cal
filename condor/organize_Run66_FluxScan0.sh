#!/bin/sh

#standard R66 config, neutrons from PuBe 
#scan "high-flux" to "low-flux" situation along straight line 
COUNTER=0
for i in 0 1 2 3 4 5 6 7 8 9
do
  DATASETIDHEX=`printf "0x%04x" ${COUNTER}`
  cat /data/chocula/villaa/k100Sim_Data/captureCal/Run66ShieldFluxScan0_PuBe_${DATASETIDHEX}_1M* |awk '{if($22==1 && $2==1){print $1"\t"$2"\t"$22}}' |awk -v offset=${i} 'END{print offset+1"\t"NR}'
  let COUNTER++
done

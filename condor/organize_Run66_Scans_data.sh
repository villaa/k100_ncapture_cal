#!/bin/sh

#standard R66 config, neutrons from PuBe in barrel
#scan "high-flux" sim vertically and radially by 1cm  increments
#vertical scan
COUNTER=0
for i in -10.0 -9.0 -8.0 -7.0 -6.0 -5.0 -4.0 -3.0 -2.0 -1.0 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0
do
  DATASETIDHEX=`printf "0x%04x" ${COUNTER}`
  cat /data/chocula/villaa/k100Sim_Data/captureCal/Run66ShieldVscan_PuBe_${DATASETIDHEX}_1M* |awk '{if($22==1 && $2==1){print $1"\t"$2"\t"$22}}' |awk -v offset=${i} 'END{print offset"\t"NR}'
  let COUNTER++
done
#radial scan (calculated to shift by 1cm increments radially)
COUNTER=0
for i in 20.520 21.227 21.934 22.641 24.055 24.7622 25.469 26.176 
do
  DATASETIDHEX=`printf "0x%04x" ${COUNTER}`
  cat /data/chocula/villaa/k100Sim_Data/captureCal/Run66ShieldRscan_PuBe_${DATASETIDHEX}_1M* |awk '{if($22==1 && $2==1){print $1"\t"$2"\t"$22}}' |awk -v side=${i} 'END{print side"\t"NR}'
  let COUNTER++
done

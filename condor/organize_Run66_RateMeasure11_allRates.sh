#!/bin/sh

#standard R66 config, neutrons from PuBe 
#scan "high-flux" to "low-flux" situation along straight line 
COUNTER=0
for i in 1 2 3 4 5 6 7 8 9 10
do
  DATASETIDHEX=`printf "0x%04x" ${COUNTER}`
  rad=`./getPositionScan_HtoL.py -r ${i}`
  num=`ls -lh /data/chocula/villaa/k100Sim_Data/captureCal/Run66ShieldRateMeasure11_PuBe_${DATASETIDHEX}_1M*000.txt |awk 'END{print NR;}'`
  rateZIP=`cat /data/chocula/villaa/k100Sim_Data/captureCal/Run66ShieldRateMeasure11_PuBe_${DATASETIDHEX}_1M*.txt |awk '{if($2==1 && $6>0.001){count[$1]++}}END{for(i in count){print i}} ' |awk 'END{print NR}'`
  rateNaIB=`cat /data/chocula/villaa/k100Sim_Data/captureCal/Run66ShieldRateMeasure11_PuBe_${DATASETIDHEX}_1M*.txt |awk '{if($2==37 && $6>3.4){count[$1]++}}END{for(i in count){print i}} ' |awk 'END{print NR}'`
  rateNaIC=`cat /data/chocula/villaa/k100Sim_Data/captureCal/Run66ShieldRateMeasure11_PuBe_${DATASETIDHEX}_1M*.txt |awk '{if($2==43 && $6>3.4){count[$1]++}}END{for(i in count){print i}} ' |awk 'END{print NR}'`
  cat /data/chocula/villaa/k100Sim_Data/captureCal/Run66ShieldRateMeasure8_PuBe_${DATASETIDHEX}_1M* |awk '{if($22==1 && $2==1){print $1"\t"$2"\t"$22}}' |awk -v rad=${rad} -v offset=${i} -v rateZIP=${rateZIP} -v rateNaIB=${rateNaIB} -v rateNaIC=${rateNaIC} -v num=${num} 'END{print rad"\t"NR"\t"rateZIP"\t"rateNaIB"\t"rateNaIC"\t"num}'
  let COUNTER++
done

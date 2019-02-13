#!/bin/sh

#standard R68 config, neutrons from PuBe 

TAG=$1
DATASET=$2
DATASETIDHEX=`printf "0x%04x" ${DATASET}`
LIST=`ls /data/chocula/villaa/k100Sim_Data/captureCal/${TAG}_${DATASETIDHEX}* |awk 'BEGIN{FS="_"}{print $9;}'|uniq`

for i in ${LIST} 
do
  ARGS=${TAG}' '${DATASET}' '${i}
  LOGPREFIX=${TAG}_${DATASETIDHEX}_${i}
  #echo ${ARGS}
  #echo ${LOGPREFIX}
  sed -e 's|ARGS|'"${ARGS}"'|g' -e 's|LOGPREFIX|'${LOGPREFIX}'|g' < condor-k100R68SimReduce > .condor
  #cat .condor
  condor_submit .condor
  rm .condor
done

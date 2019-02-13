#!/bin/sh

#standard R68 config, neutrons from PuBe 
TAG=$1
#TAG='Run68_gdirect_bknd_R68_PuBe'
#QUANTITYREGEX='10M'
QUANTITYREGEX='[0-9]+M'
DATASET=$2
#DATASET=5
DATASETIDHEX=`printf "0x%04x" ${DATASET}`
IDENTIFIER=$3

ARGS='--filedir=/data/chocula/villaa/k100Sim_Data/captureCal/ --regex='${TAG}_${DATASETIDHEX}_${QUANTITYREGEX}_${IDENTIFIER}\\S+' --outfile='/data/chocula/villaa/k100Sim_Data/captureCalhdf5/${TAG}_${DATASETIDHEX}_${IDENTIFIER}.h5''
echo ${ARGS}
./sima2py.py ${ARGS}

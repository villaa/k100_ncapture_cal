#!/bin/sh

DATASETID=$1
SOURCE=$2
NEV=$3
TEMPLATEFILE=$4
SOURCEPOSX=$5
SOURCEPOSY=$6
SOURCEPOSZ=$7
SHIELDW=$8
SHIELDL=$9
SHIELDT=${10}
SHIELDMAT=${11}
TAGNAME=${12}

DATADIR="captureCal"


DATASETIDHEX=`printf "0x%04x" ${DATASETID}`
DATE=`date +%y%m%d"_"%H%M%S"_"%N`
DAY=`date +%y%m%d`

#echo ${DATE}

if [ ${NEV} -gt 999999 ]
then
  NEVHR=$[NEV/1000000]M
elif [ ${NEV} -gt 999 ]
then
  NEVHR=$[NEV/1000]K
else
  NEVHR=${NEV}
fi

#make the simulation macro file (USE ROOT output)
sed -e 's|RADSOURCE|'${SOURCE}'|g' -e 's|THESETID|'${DATASETIDHEX}'|' -e 's|NEVENTS|'${NEV}'|' -e 's|TIMEOFDAY|'${DATE}'|' -e 's|PRIMOUT|'${PRIMOUT}'|' -e 's|DATAOUT|'${DATAOUT}'|' -e 's|TREEOUT|'${TREEOUT}'|' -e 's|DATADIR|'${DATADIR}'|' -e 's|NEVHR|'${NEVHR}'|' -e 's|SOURCEPOSX|'${SOURCEPOSX}'|' -e 's|SOURCEPOSY|'${SOURCEPOSY}'|' -e 's|SOURCEPOSZ|'${SOURCEPOSZ}'|' -e 's|SHIELDPOSX|'${SOURCEPOSX}'|' -e 's|SHIELDPOSY|'${SOURCEPOSY}'|' -e 's|SHIELDPOSZ|'${SOURCEPOSZ}'|' -e 's|SHIELDW|'${SHIELDW}'|' -e 's|SHIELDL|'${SHIELDL}'|' -e 's|SHIELDT|'${SHIELDT}'|' -e 's|SHIELDMAT|'${SHIELDMAT}'|' -e 's|TAGNAME|'${TAGNAME}'|' < ${TEMPLATEFILE}  > 'macros/'${DATADIR}'_'${SOURCE}'_'${DATASETIDHEX}'_'${DATE}'.mac'

#run the simulation job
#cat macros/${DATADIR}_${SOURCE}_${DATASETIDHEX}_${DATE}.mac
./runMacro.sh macros/${DATADIR}_${SOURCE}_${DATASETIDHEX}_${DATE}.mac

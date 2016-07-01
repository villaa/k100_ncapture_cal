#!/bin/sh

datasetno=$1
source=$2


	#get the date and make logfile names
        DATASETIDHEX=`printf "0x%04x" ${datasetno}`
        DATE=`date +%y%m%d%H%M%S`

        #create a condor file for the execution of the job
	ARGUMENTS="-o ${DATASETIDHEX}.root -set ${datasetno} -source ${source} -E"
	OUTPUTFILE=${DATASETIDHEX}_${DATE}.txt
	ERRORFILE=${DATASETIDHEX}_${DATE}.err
	SEDARG="s|THEARGUMENTS|${ARGUMENTS}|"

	LOGFILE=${DATASETIDHEX}_${DATE}.log


        sed -e "${SEDARG}" -e "s|ERRORFILE|${ERRORFILE}|" -e "s|OUTPUTFILE|${OUTPUTFILE}|" -e "s|RUNLOGFILE|${LOGFILE}|" < condor/condor-Skim  > .condorfile_${DATE}
        
        #cat .condorfile_${DATE}
        condor_submit .condorfile_${DATE}
	rm .condorfile_${DATE}

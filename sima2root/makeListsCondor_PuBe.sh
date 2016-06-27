#!/bin/sh

datasetno=$1
src=$2
simtype=$3
directory=$4
nprimaries=$5

#datasetno=18
#src=PuBe
#simtype=GenericShield
#directory=captureCal
#nprimaries=10M

        id=`printf "0x%04x" ${datasetno}`
        #create the .dat file for the chain object
        sed -e "s|IDENTIFIER|${id}|" -e "s|SOURCE|${src}|" -e "s|DIRECTORY|${directory}|" -e "s|SIMTYPE|${simtype}|" -e "s|NPRIMARIES|${nprimaries}|" < PuBe.dat.template > ${directory}_${simtype}_${src}_${id}_${nprimaries}.dat 

        #move .dat file to appropriate directory
        mv ${directory}_${simtype}_${src}_${id}_${nprimaries}.dat lists/

        #create corresponding .list file for the chain object
	ls /data/chocula/villaa/k100Sim_Data/${directory}/${simtype}_${src}_${id}_${nprimaries}_* |awk 'BEGIN{FS="[._]"}{print $6"\t"$7"\t"$8"\t1";}'  > lists/${directory}_${simtype}_${src}_${id}_${nprimaries}.list

	#get the date and make logfile names
        DATE=`date +%y%m%d%H%M%S`

        #create a condor file for the execution of the job
	ARGUMENTS="-in lists/${directory}_${simtype}_${src}_${id}_${nprimaries}.dat -o ${simtype}_${src}_${id}_${nprimaries} -dir /data/chocula/villaa/k100Sim_Data/${directory}root/ -E" 
	OUTPUTFILE=${directory}_${simtype}_${src}_${id}_${nprimaries}_${DATE}.txt
	ERRORFILE=${directory}_${simtype}_${src}_${id}_${nprimaries}_${DATE}.err
	SEDARG="s|THEARGUMENTS|${ARGUMENTS}|"

	LOGFILE=${directory}_${simtype}_${source}_${id}_${nprimaries}_${DATE}.log


        sed -e "${SEDARG}" -e "s|ERRORFILE|${ERRORFILE}|" -e "s|OUTPUTFILE|${OUTPUTFILE}|" -e "s|RUNLOGFILE|${LOGFILE}|" < condor/condor-SimA2Root  > .condorfile_${DATE}
        
        #cat .condorfile_${DATE}
        condor_submit .condorfile_${DATE}
	rm .condorfile_${DATE}
	

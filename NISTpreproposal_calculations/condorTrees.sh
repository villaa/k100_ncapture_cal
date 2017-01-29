#!/bin/sh

NEV=$1
HFAC=$2
TSC=$3
OUTNAME=$4

IDENTIFIER=${TSC}_${HFAC}_${NEV}

#root -q -b 'write.C('${NEV}','${HFAC}',"'${TSC}'","'${OUTNAME}'")'

sed -e 's|NEV|'${NEV}'|g' -e 's|HFAC|'${HFAC}'|g' -e 's|TSC|'${TSC}'|g' -e 's|ROOTFILE|'${OUTNAME}'|g' -e 's|IDENTIFIER|'${IDENTIFIER}'|g' < condor-Cascade > .condorjob

condor_submit .condorjob
rm .condorjob

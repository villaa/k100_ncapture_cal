#!/bin/sh

pwd
ls setup.sh
. ./setup.sh

CMSload=`condor_q -wide |grep genShieldSimCondense_CMS.sh|awk '{print $9}'`
CDMSload=`condor_q -wide |grep genShieldSimCondense.sh|awk '{print $9}'`

echo "CMS load: "${CMSload} 
echo "CDMS load: "${CDMSload} 

CMSmax=10
CDMSmax=10

CMSsubmit=$((${CMSmax}-${CMSload}))
CDMSsubmit=$((${CDMSmax}-${CDMSload}))

echo "CMS will submit: "${CMSsubmit}
echo "CDMS will submit: "${CDMSsubmit}

./condork100Sim_GenericShielding_CMS -n ${CMSsubmit} -src R68_PuBe -set 6 -ngen 10000000 -template templates/Run68_gdirect_bknd.mac.template -merge -sourcepos `./getPositionScan_HtoL.py --n 10 10` -shieldsize 40.0 40.0 40.0 -shieldmat Poly -exe
./condork100Sim_GenericShielding -n ${CDMSsubmit} -src R68_PuBe -set 6 -ngen 10000000 -template templates/Run68_gdirect_bknd.mac.template -merge -sourcepos `./getPositionScan_HtoL.py --n 10 10` -shieldsize 40.0 40.0 40.0 -shieldmat Poly -exe

#!/bin/sh

#standard R66 config, neutrons from PuBe 
#scan "high-flux" to "low-flux" situation along straight line 
COUNTER=0
for i in 1 2 3 4 5 6 7 8 9 10 
do
  ./condork100Sim_GenericShielding -n 10 -src PuBe -set ${COUNTER} -ngen 1000000 -template templates/Run66Shield_FluxScan1.mac.template -merge -sourcepos `./getPositionScan_HtoL.py --n 10 ${i}` -shieldsize 40.0 40.0 40.0 -shieldmat Poly -exe
  let COUNTER++
done

#!/bin/sh

#standard R66 config, neutrons from PuBe 
#scan "high-flux" to "low-flux" situation along straight line 
COUNTER=0
for i in 2 4 6 8 10 12 14 16 18 20 
do
  ./condork100Sim_GenericShielding -n 10 -src PuBe -set ${COUNTER} -ngen 1000000 -template templates/Run66Shield_RateMeasure11.mac.template -merge -sourcepos ${i} 0.0 0.0 -shieldsize 40.0 40.0 40.0 -shieldmat Poly -exe
  let COUNTER++
done

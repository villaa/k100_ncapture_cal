#!/bin/sh

#standard R66 config, neutrons from PuBe in barrel
#scan "high-flux" sim vertically and radially by 1cm  increments
#vertical scan
COUNTER=0
for i in -5.0 -4.0 -3.0 -2.0 -1.0 1.0 2.0 3.0 4.0 5.0 
do
  ./condork100Sim_GenericShielding -n 1 -src PuBe -set ${COUNTER} -ngen 1000000 -template templates/Run66Shield_nearCryostat_Rscan.mac.template -merge -sourcepos 23.348 23.348 ${i} -shieldsize 40.0 40.0 40.0 -shieldmat Poly -exe
  let COUNTER++
done
#radial scan (calculated to shift by 1cm increments radially)
COUNTER=0
for i in 20.520 21.227 21.934 22.641 24.055 24.7622 25.469 26.176 
do
  ./condork100Sim_GenericShielding -n 1 -src PuBe -set ${COUNTER} -ngen 1000000 -template templates/Run66Shield_nearCryostat_Vscan.mac.template -merge -sourcepos ${i} ${i} 0.0 -shieldsize 40.0 40.0 40.0 -shieldmat Poly -exe
  let COUNTER++
done

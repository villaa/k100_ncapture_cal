#!/bin/sh

#The following were done with an errant pube_skim.dat source neutron energy file.  
#step by 10 cm in thickness and source distance from the side try 100M primaries
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 1 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -70.0 0.0 0.0 -shieldsize 20.0 20.0 40.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 2 -ngen 1000000 -template templates/pube.mac.template -merge -sourcepos -60.0 0.0 0.0 -shieldsize 20.0 20.0 30.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 3 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -50.0 0.0 0.0 -shieldsize 20.0 20.0 20.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 4 -ngen 1000000 -template templates/pube.mac.template -merge -sourcepos -80.0 0.0 0.0 -shieldsize 20.0 20.0 50.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 5 -ngen 1000000 -template templates/pube.mac.template -merge -sourcepos -90.0 0.0 0.0 -shieldsize 20.0 20.0 60.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 6 -ngen 1000000 -template templates/pube.mac.template -merge -sourcepos -100.0 0.0 0.0 -shieldsize 20.0 20.0 70.0 -shieldmat Poly -exe

#pube_skim.dat has now been corrected (06/16/16) so redo all the above at least with new set id numbers  
#step by 10 cm in thickness and source distance from the side try 100M primaries
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 7 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -70.0 0.0 0.0 -shieldsize 20.0 20.0 40.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 8 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -60.0 0.0 0.0 -shieldsize 20.0 20.0 30.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 9 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -50.0 0.0 0.0 -shieldsize 20.0 20.0 20.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 10 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -80.0 0.0 0.0 -shieldsize 20.0 20.0 50.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 11 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -90.0 0.0 0.0 -shieldsize 20.0 20.0 60.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 12 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -100.0 0.0 0.0 -shieldsize 20.0 20.0 70.0 -shieldmat Poly -exe

#try with larger lateral shielding  
#step by 10 cm in thickness and source distance from the side try 100M primaries
#./condork100Sim_GenericShielding -n 10 -src PuBe -set 13 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -70.0 0.0 0.0 -shieldsize 40.0 40.0 40.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src PuBe -set 14 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -60.0 0.0 0.0 -shieldsize 40.0 40.0 30.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src PuBe -set 15 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -50.0 0.0 0.0 -shieldsize 40.0 40.0 20.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src PuBe -set 16 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -80.0 0.0 0.0 -shieldsize 40.0 40.0 50.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src PuBe -set 17 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -90.0 0.0 0.0 -shieldsize 40.0 40.0 60.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src PuBe -set 18 -ngen 10000000 -template templates/pube.mac.template -merge -sourcepos -100.0 0.0 0.0 -shieldsize 40.0 40.0 70.0 -shieldmat Poly -exe

#try with larger lateral shielding and lower source energy 
#step by 10 cm in thickness and source distance from the side try 100M primaries
#./condork100Sim_GenericShielding -n 10 -src n24kev -set 19 -ngen 10000000 -template templates/n24kev.mac.template -merge -sourcepos -70.0 0.0 0.0 -shieldsize 40.0 40.0 40.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src n24kev -set 20 -ngen 10000000 -template templates/n24kev.mac.template -merge -sourcepos -60.0 0.0 0.0 -shieldsize 40.0 40.0 30.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src n24kev -set 21 -ngen 10000000 -template templates/n24kev.mac.template -merge -sourcepos -50.0 0.0 0.0 -shieldsize 40.0 40.0 20.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src n24kev -set 22 -ngen 10000000 -template templates/n24kev.mac.template -merge -sourcepos -80.0 0.0 0.0 -shieldsize 40.0 40.0 50.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src n24kev -set 23 -ngen 10000000 -template templates/n24kev.mac.template -merge -sourcepos -90.0 0.0 0.0 -shieldsize 40.0 40.0 60.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src n24kev -set 24 -ngen 10000000 -template templates/n24kev.mac.template -merge -sourcepos -100.0 0.0 0.0 -shieldsize 40.0 40.0 70.0 -shieldmat Poly -exe

#try with larger lateral shielding AND gamma coincidence
#step by 10 cm in thickness and source distance from the side try 100M primaries
#./condork100Sim_GenericShielding -n 10 -src PuBeCoin -set 25 -ngen 10000000 -template templates/pubeCoin.mac.template -merge -sourcepos -70.0 0.0 0.0 -shieldsize 40.0 40.0 40.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src PuBeCoin -set 26 -ngen 10000000 -template templates/pubeCoin.mac.template -merge -sourcepos -60.0 0.0 0.0 -shieldsize 40.0 40.0 30.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBeCoin -set 27 -ngen 100000000 -template templates/pubeCoin.mac.template -merge -sourcepos -50.0 0.0 0.0 -shieldsize 40.0 40.0 20.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src PuBeCoin -set 28 -ngen 10000000 -template templates/pubeCoin.mac.template -merge -sourcepos -80.0 0.0 0.0 -shieldsize 40.0 40.0 50.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src PuBeCoin -set 29 -ngen 10000000 -template templates/pubeCoin.mac.template -merge -sourcepos -90.0 0.0 0.0 -shieldsize 40.0 40.0 60.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src PuBeCoin -set 30 -ngen 10000000 -template templates/pubeCoin.mac.template -merge -sourcepos -100.0 0.0 0.0 -shieldsize 40.0 40.0 70.0 -shieldmat Poly -exe

#try gamma coincidence with thermal neutrons right at detector
#step by 10 cm in thickness and source distance from the side try 100M primaries
#./condork100Sim_GenericShielding -n 10 -src thermalAtDetCoin -set 31 -ngen 10000000 -template templates/thermalAtDetCoin.mac.template -merge -exe

#try with larger lateral shielding AND gamma coincidence and 2.45 MeV neutrons
#step by 10 cm in thickness and source distance from the side try 100M primaries
#./condork100Sim_GenericShielding -n 10 -src DDCoin -set 32 -ngen 10000000 -template templates/n2-45MeVCoin.mac.template -merge -sourcepos -70.0 0.0 0.0 -shieldsize 40.0 40.0 40.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src DDCoin -set 33 -ngen 10000000 -template templates/n2-45MeVCoin.mac.template -merge -sourcepos -60.0 0.0 0.0 -shieldsize 40.0 40.0 30.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src DDCoin -set 34 -ngen 100000000 -template templates/n2-45MeVCoin.mac.template -merge -sourcepos -50.0 0.0 0.0 -shieldsize 40.0 40.0 20.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src DDCoin -set 35 -ngen 10000000 -template templates/n2-45MeVCoin.mac.template -merge -sourcepos -80.0 0.0 0.0 -shieldsize 40.0 40.0 50.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src DDCoin -set 36 -ngen 10000000 -template templates/n2-45MeVCoin.mac.template -merge -sourcepos -90.0 0.0 0.0 -shieldsize 40.0 40.0 60.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 10 -src DDCoin -set 37 -ngen 10000000 -template templates/n2-45MeVCoin.mac.template -merge -sourcepos -100.0 0.0 0.0 -shieldsize 40.0 40.0 70.0 -shieldmat Poly -exe

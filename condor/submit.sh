#!/bin/sh

#step by 10 cm in thickness and source distance from the side try 100M primaries
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 1 -ngen 1000000 -template templates/pube.mac.template -merge -sourcepos -70.0 0.0 0.0 -shieldsize 20.0 20.0 40.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 2 -ngen 1000000 -template templates/pube.mac.template -merge -sourcepos -60.0 0.0 0.0 -shieldsize 20.0 20.0 30.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 3 -ngen 1000000 -template templates/pube.mac.template -merge -sourcepos -50.0 0.0 0.0 -shieldsize 20.0 20.0 20.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 4 -ngen 1000000 -template templates/pube.mac.template -merge -sourcepos -80.0 0.0 0.0 -shieldsize 20.0 20.0 50.0 -shieldmat Poly -exe
#./condork100Sim_GenericShielding -n 100 -src PuBe -set 5 -ngen 1000000 -template templates/pube.mac.template -merge -sourcepos -90.0 0.0 0.0 -shieldsize 20.0 20.0 60.0 -shieldmat Poly -exe
./condork100Sim_GenericShielding -n 100 -src PuBe -set 6 -ngen 1000000 -template templates/pube.mac.template -merge -sourcepos -100.0 0.0 0.0 -shieldsize 20.0 20.0 70.0 -shieldmat Poly -exe

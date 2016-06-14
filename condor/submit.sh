#!/bin/sh

#step by 10 cm in thickness and source distance from the side try 100M primaries
./condork100Sim_GenericShielding -n 100 -src PuBe -set 1 -ngen 1000000 -template templates/pube.mac.template -merge -sourcepos -70.0 0.0 0.0 -shieldsize 20.0 20.0 40.0 -shieldmat Poly -exe

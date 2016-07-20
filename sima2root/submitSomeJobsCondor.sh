#!/bin/sh


#for i in $(seq 1 18) 
#do
#  ./makeListsCondor_PuBe.sh ${i} PuBe GenericShield captureCal 10M
#done
#for i in $(seq 19 24) 
#do
#  ./makeListsCondor_PuBe.sh ${i} n24kev GenericShield captureCal 10M
#done
./makeListsCondor_PuBe.sh 27 PuBeCoin GenericShield captureCal 10M
#./makeListsCondor_PuBe.sh 34 DDCoin GenericShield captureCal 10M
#./makeListsCondor_PuBe.sh 27 PuBeCoin GenericShield captureCal 100M
#./makeListsCondor_PuBe.sh 34 DDCoin GenericShield captureCal 100M

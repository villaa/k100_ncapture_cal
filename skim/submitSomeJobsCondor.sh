#!/bin/sh


for i in $(seq 0 0) 
do
  ./makeListsCondor_Skim_Run66ShieldTest.sh ${i} PuBe 
done
#for i in $(seq 20 24) 
#do
#  ./makeListsCondor_Skim.sh ${i} n24kev
#done

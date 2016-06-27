#!/bin/sh


for i in $(seq 13 18) 
do
  ./makeListsCondor_Skim.sh ${i} PuBe 
done
for i in $(seq 20 24) 
do
  ./makeListsCondor_Skim.sh ${i} n24kev
done

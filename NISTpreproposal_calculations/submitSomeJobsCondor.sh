#!/bin/sh


for i in 1 10 100 1000 
do
  FILE=First${i}
  ./condorTrees.sh 100000 $i First cascades_${FILE}.root
  FILE=Second${i}
  ./condorTrees.sh 100000 $i Second cascades_${FILE}.root
  FILE=Third${i}
  ./condorTrees.sh 100000 $i Third cascades_${FILE}.root
done

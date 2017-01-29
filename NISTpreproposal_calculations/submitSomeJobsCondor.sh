#!/bin/sh


for i in 1 10 100 1000 
do
  ./condorTrees.sh 100 $i First cascades.root
  ./condorTrees.sh 100 $i Second cascades.root
  ./condorTrees.sh 100 $i Third cascades.root
done

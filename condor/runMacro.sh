#!/bin/sh

MACRO=$1

k100Sim -p ${MACRO} << EOF
exit
EOF

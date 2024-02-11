#!/bin/bash
GASS_PORT=34495
LOCAL_HOST=david.ccgc.mastercpd.upv.es
NUMBER=$1
# Creacion de los RSL
i=1
while [ $i -le $NUMBER ]
do
echo "&" >script_$i.rsl
echo "(count = 1)" >>script_$i.rsl
echo "(executable = /usr/bin/octave)" >>script_$i.rsl
echo "(arguments = test_or.m 4 1.$i )" >>script_$i.rsl
echo "(rsl_substitution = (GASS_URL
https://$LOCAL_HOST:${GASS_PORT}/home/ccgc/Evidencias/Grid/04_Programacion/P2))">>script_$i.rsl
echo "(stdout = \$(GASS_URL)/miStdout_$i)" >>script_$i.rsl
echo "(stderr = \$(GASS_URL)/miStderr_$i)" >>script_$i.rsl
echo "(file_stage_in=( \$(GASS_URL)/test_or.m test_or.m ) )" >>script_$i.rsl
i=$(( i+1 ))
done

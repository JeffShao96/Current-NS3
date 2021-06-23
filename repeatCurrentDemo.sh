#!/bin/bash
for d1 in {1..1000}
do
    for d2 in {1..1000}
    do
    ./waf --run "currentDemo --delay1=$d1 --delay2=$d2">>log.out 2>&1
    done
done

#!/bin/bash
d0=0
d1=0
start_time=`date +%s`
echo "Start running the scratch at $start_time_s">log.out
start_time_s=`date`
for d0 in {1..1000}
do
    for d1 in {1..1000}
    do
    echo "delay0 is $d0, delay1 is $d1"
    ./waf --run "currentDemo --delay0=$d0 --delay1=$d1"
    done
done
end_time_s=`date`
end_time=`date +%s`
run=$[$end_time-$start_time]
echo "Finish running the scratch at $start_time_s">>log.out
echo "Total running time: $run seconds">>log.out
echo "Finish running the scratch at $start_time_s"
echo "Total running time: $run seconds"

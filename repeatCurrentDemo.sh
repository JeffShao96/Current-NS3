#!/bin/bash
a=0
b=0
start_time=`date +%s`
echo "Start running the scratch at $start_time_s">log.out
start_time_s=`date`
for a in {1..1000}
do
    for b in {1..1000}
    do
    echo "delayA is $a, delayB is $b"
    ./waf --run "currentDemo --delayA=$a --delayB=$b"
    done
done
end_time_s=`date`
end_time=`date +%s`
run=$[$end_time-$start_time]
echo "Finish running the scratch at $start_time_s">>log.out
echo "Total running time: $run seconds">>log.out
echo "Finish running the scratch at $start_time_s"
echo "Total running time: $run seconds"
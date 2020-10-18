# Current-NS3
This demo will show how Brute Force solve the problem.

## Code

To find the range of difference between the receiving time of two packages using the brute force method with the current NS-3, we write two scripts. The shell script [repeatCurrentDemo.sh](./repeatCurrentDemo.sh) enumerates all possible combinations of d0 and d1, and runs an NS-3 simulation for each combination.

```bash
...
for d0 in {1..1000}
do
    for d1 in {1..1000}
    do
    ./waf --run "currentDemo --delayA=$d0 --delayB=$d1"
    done
done
...
```


The NS-3 script [currentDemo.cc](./scratch/currentDemo.cc) simulates the network according to the link delays specified in the arguments. 

```cpp
...
pointToPoint[0].SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
pointToPoint[0].SetChannelAttribute ("Delay", TimeValue (Time (delay0)));
pointToPoint[1].SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
pointToPoint[1].SetChannelAttribute ("Delay", TimeValue (Time (delay1)));
...
```

In addition, we modify NS-3 file [udp-server.cc](./src/applications/model/udp-server.cc) to keep track of the packet arrival times and then calculate and print out the difference between the receiving time of two packages.

## Demo
You can repeat the demo by using following command:
```bash
./waf configure
./repeatCurrentDemo.sh
```

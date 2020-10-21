# Solving an exhaustive testing problem using current NS-3


This repository contains the necessary code to solve the following exhasutive testing problem using the current NS-3. You can find more information about the problem in this [short paper](https://cse.unl.edu/~xu/research/Sym_NS_3_Draft.pdf). 

Exhaustive testing problem: Two senders and one receiver are connected by two point-to-point links. Both senders simultaneously send a UDP packet to the receiver. What is the range of all possible differences between the arrival times of these two packets if each link has an uncertain delay between 1 and 1000ms?

We can use the brute force method with the current NS-3 to simulate all possible cases (a total of 1000*1000=1,000,000 cases). You can download the corresponding scripts and code in this repository (including [repeatCurrentDemo.sh](./repeatCurrentDemo.sh), [currentDemo.cc](./scratch/currentDemo.cc), and [udp-server.cc](./src/applications/model/udp-server.cc)). It takes a total of 521,900 seconds to run all 1,000,000 simulations, and the simulation result is presented and discussed in the [short paper](https://cse.unl.edu/~xu/research/Sym_NS_3_Draft.pdf). 

We propose a more efficient method using our proposed [Symbolic NS-3](https://github.com/JeffShao96/Symbolic-NS3). It takes only 33 seconds to get the simulation result using Symbolic NS-3, and the simulation result is presented and discussed in the [short paper](https://cse.unl.edu/~xu/research/Sym_NS_3_Draft.pdf). 

Below is the instruction to run the brute force method. 


## Instruction
You can run the brute force method using following command:
```bash
./waf configure
./repeatCurrentDemo.sh
```
## Exhaustive Testing Demo Code

To find the range of the difference between the arrival times of two packets using the brute force method with the current NS-3, we write two scripts. The shell script [repeatCurrentDemo.sh](./repeatCurrentDemo.sh) enumerates all possible 1,000,000 combinations of the link delays, and runs an NS-3 simulation for each combination.

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

In addition, we modify NS-3 file [udp-server.cc](./src/applications/model/udp-server.cc) to keep track of the packet arrival times and then calculate and print out their difference.

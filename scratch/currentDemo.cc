#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ctime"

//Network Topology
//
// snda -------rcv------- sndb
//    point-to-point
//

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("CurrentNS3ScriptExample");

int
main (int argc, char *argv[])
{

  Time::SetResolution (Time::MS);

  uint32_t delay0 = 0;
  uint32_t delay1 = 0;
  CommandLine cmd (__FILE__);
  cmd.AddValue ("delayA", "The delay for link between snda and rcv.", delay0);
  cmd.AddValue ("delayB", "The delay for link between snda and rcv.", delay1);
  cmd.Parse (argc, argv);

  NodeContainer nodes;
  nodes.Create (3);

  std::vector<NodeContainer> nodeAdjacencyList (2);
  nodeAdjacencyList[0] = NodeContainer (nodes.Get (0), nodes.Get (2));
  nodeAdjacencyList[1] = NodeContainer (nodes.Get (1), nodes.Get (2));

  std::vector<PointToPointHelper> pointToPoint (2);
  pointToPoint[0].SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint[0].SetChannelAttribute ("Delay", TimeValue (Time (delay0)));

  pointToPoint[1].SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint[1].SetChannelAttribute ("Delay", TimeValue (Time (delay1)));

  std::vector<NetDeviceContainer> devices (2);
  devices[0] = pointToPoint[0].Install (nodeAdjacencyList[0]);
  devices[1] = pointToPoint[1].Install (nodeAdjacencyList[1]);

  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;
  std::vector<Ipv4InterfaceContainer> interfaces (2);
  for (uint32_t i = 0; i < 2; i++)
    {
      std::ostringstream subset;
      subset << "10.1." << i + 1 << ".0";
      address.SetBase (subset.str ().c_str (), "255.255.255.0");
      interfaces[i] = address.Assign (devices[i]);
    }

  UdpServerHelper server1 (2333);

  ApplicationContainer rcv = server1.Install (nodes.Get (2));
  rcv.Start (Seconds (1.0));
  rcv.Stop (Seconds (10.0));

  UdpClientHelper client1 (interfaces[0].GetAddress (1), 2333);
  client1.SetAttribute ("MaxPackets", UintegerValue (1));
  client1.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  client1.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer snda = client1.Install (nodes.Get (0));
  snda.Start (Seconds (1.0));
  snda.Stop (Seconds (10.0));

  UdpClientHelper client2 (interfaces[1].GetAddress (1), 2333);
  client2.SetAttribute ("MaxPackets", UintegerValue (1));
  client2.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  client2.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer sndb = client2.Install (nodes.Get (1));
  sndb.Start (Seconds (1.0));
  sndb.Stop (Seconds (10.0));

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}

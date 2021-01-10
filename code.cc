 #include <fstream>
 #include "ns3/core-module.h"
 #include "ns3/internet-module.h"
 #include "ns3/csma-module.h"
 #include "ns3/internet-apps-module.h"
 #include "ns3/ipv4-static-routing-helper.h"
 #include "ns3/ipv4-routing-table-entry.h"
 #include "ns3/netanim-module.h"
 #include "ns3/mobility-module.h"

 using namespace ns3;
 
 NS_LOG_COMPONENT_DEFINE ("RipSimpleRouting");
 
 void TearDownLink (Ptr<Node> nodeA, Ptr<Node> nodeB, uint32_t interfaceA, uint32_t interfaceB)
 {
   nodeA->GetObject<Ipv4> ()->SetDown (interfaceA);
   nodeB->GetObject<Ipv4> ()->SetDown (interfaceB);
 }
 
 int main (int argc, char **argv)
 {
   bool printRoutingTables = true;
   bool showPings = true;
   std::string SplitHorizon ("PoisonReverse");
 
   if (SplitHorizon == "NoSplitHorizon")
     {
       Config::SetDefault ("ns3::Rip::SplitHorizon", EnumValue (RipNg::NO_SPLIT_HORIZON));
     }
   else if (SplitHorizon == "SplitHorizon")
     {
       Config::SetDefault ("ns3::Rip::SplitHorizon", EnumValue (RipNg::SPLIT_HORIZON));
     }
   else
     {
       Config::SetDefault ("ns3::Rip::SplitHorizon", EnumValue (RipNg::POISON_REVERSE));
     }
 
   NS_LOG_INFO ("Create nodes.");
   Ptr<Node> a = CreateObject<Node> (); //src
   Names::Add ("A", a);                 // SrcNode, src
   Ptr<Node> b = CreateObject<Node> ();
   Names::Add ("B", b);
   Ptr<Node> c = CreateObject<Node> ();
   Names::Add ("C", c);
   Ptr<Node> d = CreateObject<Node> ();
   Names::Add ("D", d);
   Ptr<Node> e = CreateObject<Node> ();
   Names::Add ("E", e);
   Ptr<Node> f = CreateObject<Node> ();
   Names::Add ("F", f);
   Ptr<Node> g = CreateObject<Node> ();
   Names::Add ("G", g);
   Ptr<Node> h = CreateObject<Node> ();
   Names::Add ("H", h);
   Ptr<Node> i = CreateObject<Node> ();
   Names::Add ("I", i);
   Ptr<Node> j = CreateObject<Node> ();
   Names::Add ("J", j);
   Ptr<Node> k = CreateObject<Node> ();
   Names::Add ("K", k);
   Ptr<Node> r1 = CreateObject<Node> ();
   Names::Add ("R1", r1);
   Ptr<Node> r2 = CreateObject<Node> ();
   Names::Add ("R2", r2);
   Ptr<Node> r3 = CreateObject<Node> ();
   Names::Add ("R3", r3);
   Ptr<Node> r4 = CreateObject<Node> ();
   Names::Add ("R4", r4);
   Ptr<Node> r5 = CreateObject<Node> ();
   Names::Add ("R5", r5);
   Ptr<Node> r6 = CreateObject<Node> ();
   Names::Add ("R6", r6);

   NodeContainer net1 (a, r1);
   NodeContainer net2 (b, r1);
   NodeContainer net3 (c, r1);

   NodeContainer net4 (d, r2);
   NodeContainer net5 (e, r2);
   NodeContainer net6 (f, r2);
   NodeContainer net7 (g, r2);

   NodeContainer net8 (h, r5);
   NodeContainer net9 (i, r5);

   NodeContainer net10 (j, r6);
   NodeContainer net11 (k, r6);

   NodeContainer net12 (r1, r3);
   NodeContainer net13 (r3, r4);
   NodeContainer net14 (r3, r5);

   NodeContainer net15 (r4, r2);
   NodeContainer net16 (r4, r6);
   NodeContainer net17 (r4, r5);
   NodeContainer routers (r1, r2, r3, r4, r5);
   NodeContainer routers2 (r6);
   NodeContainer nodes (a, b, c, d, e); 
   NodeContainer nodes2 (f, g, h, i, j);
   NodeContainer nodes3 (k);

   NS_LOG_INFO ("Create channels.");
   CsmaHelper csma;
   csma.SetChannelAttribute ("DataRate", DataRateValue (5000000));
   csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
   NetDeviceContainer ndc1 = csma.Install (net1);
   NetDeviceContainer ndc2 = csma.Install (net2);
   NetDeviceContainer ndc3 = csma.Install (net3);
   NetDeviceContainer ndc4 = csma.Install (net4);
   NetDeviceContainer ndc5 = csma.Install (net5);
   NetDeviceContainer ndc6 = csma.Install (net6);
   NetDeviceContainer ndc7 = csma.Install (net7);
   NetDeviceContainer ndc8 = csma.Install (net8);
   NetDeviceContainer ndc9 = csma.Install (net9);
   NetDeviceContainer ndc10 = csma.Install (net10);
   NetDeviceContainer ndc11 = csma.Install (net11);
   NetDeviceContainer ndc12 = csma.Install (net12);
   NetDeviceContainer ndc13 = csma.Install (net13);
   NetDeviceContainer ndc14 = csma.Install (net14);
   NetDeviceContainer ndc15 = csma.Install (net15);
   NetDeviceContainer ndc16 = csma.Install (net16);
   NetDeviceContainer ndc17 = csma.Install (net17);
 
   NS_LOG_INFO ("Create IPv4 and routing");
   RipHelper ripRouting;
 
   // Rule of thumb:
   // Interfaces are added sequentially, starting from 0
   // However, interface 0 is always the loopback...
   ripRouting.ExcludeInterface (r1, 1);
   ripRouting.ExcludeInterface (r1, 2);
   ripRouting.ExcludeInterface (r1, 3);

   ripRouting.ExcludeInterface (r2, 1);
   ripRouting.ExcludeInterface (r2, 2);
   ripRouting.ExcludeInterface (r2, 3);
   ripRouting.ExcludeInterface (r2, 4);

   ripRouting.ExcludeInterface (r5, 1);
   ripRouting.ExcludeInterface (r5, 2);

   ripRouting.ExcludeInterface (r6, 1);
   ripRouting.ExcludeInterface (r6, 2);

 
   ripRouting.SetInterfaceMetric (r4, 4, 5);
   ripRouting.SetInterfaceMetric (r5, 4, 5);
 
   Ipv4ListRoutingHelper listRH;
   listRH.Add (ripRouting, 0);
 //  Ipv4StaticRoutingHelper staticRh;
 //  listRH.Add (staticRh, 5);
 
   InternetStackHelper internet;
   internet.SetIpv6StackInstall (false);
   internet.SetRoutingHelper (listRH);
   internet.Install (routers);
   internet.Install (routers2);

   InternetStackHelper internetNodes;
   internetNodes.SetIpv6StackInstall (false);
   internetNodes.Install (nodes);
   internetNodes.Install (nodes2);
   internetNodes.Install (nodes3);

 
   // Assign addresses.
   // The source and destination networks have global addresses
   // The "core" network just needs link-local addresses for routing.
   // We assign global addresses to the routers as well to receive
   // ICMPv6 errors.
   NS_LOG_INFO ("Assign IPv4 Addresses.");
   Ipv4AddressHelper ipv4;
 
   ipv4.SetBase (Ipv4Address ("10.0.0.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic1 = ipv4.Assign (ndc1); // a-r1
 
   ipv4.SetBase (Ipv4Address ("10.0.1.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic2 = ipv4.Assign (ndc2); // b-r1
 
   ipv4.SetBase (Ipv4Address ("10.0.2.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic3 = ipv4.Assign (ndc3); // c-r1
 
   ipv4.SetBase (Ipv4Address ("10.0.3.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic4 = ipv4.Assign (ndc4); // d-r2
 
   ipv4.SetBase (Ipv4Address ("10.0.4.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic5 = ipv4.Assign (ndc5); // e-r2
 
   ipv4.SetBase (Ipv4Address ("10.0.5.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic6 = ipv4.Assign (ndc6); //f-r2
 
   ipv4.SetBase (Ipv4Address ("10.0.6.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic7 = ipv4.Assign (ndc7); // g-r2

   ipv4.SetBase (Ipv4Address ("10.0.7.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic8 = ipv4.Assign (ndc8); //h-r5
 
   ipv4.SetBase (Ipv4Address ("10.0.8.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic9 = ipv4.Assign (ndc9); //i-r5
 
   ipv4.SetBase (Ipv4Address ("10.0.9.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic10 = ipv4.Assign (ndc10); //j-r6

   ipv4.SetBase (Ipv4Address ("10.0.10.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic11 = ipv4.Assign (ndc11); //k-r6
 
   ipv4.SetBase (Ipv4Address ("10.0.11.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic12 = ipv4.Assign (ndc12); // r1-r3
 
   ipv4.SetBase (Ipv4Address ("10.0.12.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic13 = ipv4.Assign (ndc13); // r3-r4
 
   ipv4.SetBase (Ipv4Address ("10.0.13.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic14 = ipv4.Assign (ndc14); // r3-r5
 
   ipv4.SetBase (Ipv4Address ("10.0.14.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic15 = ipv4.Assign (ndc15); // r4-r2
 
   ipv4.SetBase (Ipv4Address ("10.0.15.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic16 = ipv4.Assign (ndc16); // r4-r6
 
   ipv4.SetBase (Ipv4Address ("10.0.16.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic17 = ipv4.Assign (ndc17); // r4-r5
 
   Ptr<Ipv4StaticRouting> staticRouting1;
   staticRouting1 = Ipv4RoutingHelper::GetRouting <Ipv4StaticRouting> (a->GetObject<Ipv4> ()->GetRoutingProtocol ());
   staticRouting1->SetDefaultRoute ("10.0.0.2", 1 );
   staticRouting1 = Ipv4RoutingHelper::GetRouting <Ipv4StaticRouting> (k->GetObject<Ipv4> ()->GetRoutingProtocol ());
   staticRouting1->SetDefaultRoute ("10.0.10.2", 1 );

   Ptr<Ipv4StaticRouting> staticRouting2;
   staticRouting2 = Ipv4RoutingHelper::GetRouting <Ipv4StaticRouting> (g->GetObject<Ipv4> ()->GetRoutingProtocol ());
   staticRouting2->SetDefaultRoute ("10.0.6.2", 1 );
   staticRouting2 = Ipv4RoutingHelper::GetRouting <Ipv4StaticRouting> (h->GetObject<Ipv4> ()->GetRoutingProtocol ());
   staticRouting2->SetDefaultRoute ("10.0.7.2", 1 );
 
   if (printRoutingTables)
     {
       RipHelper routingHelper;
 
       Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> (&std::cout);
 
       routingHelper.PrintRoutingTableAt (Seconds (10.0), r1, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (10.0), r2, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (10.0), r3, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (10.0), r4, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (10.0), r5, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (10.0), r6, routingStream);

       routingHelper.PrintRoutingTableAt (Seconds (40.0), r1, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (40.0), r2, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (40.0), r3, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (40.0), r4, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (40.0), r5, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (40.0), r6, routingStream);

       routingHelper.PrintRoutingTableAt (Seconds (80.0), r1, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (80.0), r2, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (80.0), r3, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (80.0), r4, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (80.0), r5, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (80.0), r6, routingStream);     
     }
 
   NS_LOG_INFO ("Create Applications.");
   uint32_t packetSize = 1024;
   Time interPacketInterval = Seconds (1.0);
   V4PingHelper ping1 ("10.0.10.1");
   V4PingHelper ping2 ("10.0.7.1");

 
   ping1.SetAttribute ("Interval", TimeValue (interPacketInterval));
   ping1.SetAttribute ("Size", UintegerValue (packetSize));
   ping2.SetAttribute ("Interval", TimeValue (interPacketInterval));
   ping2.SetAttribute ("Size", UintegerValue (packetSize));
   if (showPings)
     {
       ping1.SetAttribute ("Verbose", BooleanValue (true));
       ping2.SetAttribute ("Verbose", BooleanValue (true));

     }
   ApplicationContainer apps1 = ping1.Install (a);
   ApplicationContainer apps2 = ping2.Install (g);
   apps1.Start (Seconds (0.0));
   apps1.Stop (Seconds (80.0));
   apps2.Start (Seconds (0.0));
   apps2.Stop (Seconds (80.0));
 
   AsciiTraceHelper ascii;
   //csma.EnableAsciiAll (ascii.CreateFileStream ("rip-simple-routing.tr"));
   csma.EnablePcapAll ("rip-simple-routing", true);

 
   Simulator::Schedule (Seconds (25), &TearDownLink, r3, r4, 2, 1);

 
   /* Now, do the actual simulation. */
   NS_LOG_INFO ("Run Simulation.");
   Simulator::Stop (Seconds (90.0));

  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (nodes);
  mobility.Install (nodes2);
  mobility.Install (nodes3);
  mobility.Install (routers);
  mobility.Install (routers2);
  AnimationInterface anim("anim.xml");

  std::cout << "set position for nodes" << std::endl;

  Ptr<ConstantPositionMobilityModel> na = nodes.Get (0)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> nb = nodes.Get (1)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> nc = nodes.Get (2)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> nd = nodes.Get (3)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> ne = nodes.Get (4)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> nf = nodes2.Get (0)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> ng = nodes2.Get (1)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> nh = nodes2.Get (2)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> ni = nodes2.Get (3)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> nj = nodes2.Get (4)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> nk = nodes3.Get (0)->GetObject<ConstantPositionMobilityModel> ();

  Ptr<ConstantPositionMobilityModel> rr1 = routers.Get (0)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> rr2 = routers.Get (1)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> rr3 = routers.Get (2)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> rr4 = routers.Get (3)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> rr5 = routers.Get (4)->GetObject<ConstantPositionMobilityModel> ();
  Ptr<ConstantPositionMobilityModel> rr6 = routers2.Get (0)->GetObject<ConstantPositionMobilityModel> ();

  na->SetPosition (Vector ( 0.0, 0.0, 0  ));
  nb->SetPosition (Vector ( 10.0, 0.0, 0  ));
  nc->SetPosition (Vector ( 20.0, 0.0, 0  ));
  nd->SetPosition (Vector ( 80.0, 0.0, 0  ));
  ne->SetPosition (Vector ( 90.0, 0.0, 0  ));
  nf->SetPosition (Vector ( 100.0, 0.0, 0  ));
  ng->SetPosition (Vector ( 110.0, 0.0, 0  ));
  nh->SetPosition (Vector ( 10.0, 100.0, 0  ));
  ni->SetPosition (Vector ( 20.0, 100.0, 0  ));
  nj->SetPosition (Vector ( 90.0, 100.0, 0  ));
  nk->SetPosition (Vector ( 100.0, 100.0, 0  ));
  rr1->SetPosition (Vector ( 30.0, 20.0, 0  ));
  rr2->SetPosition (Vector ( 80.0, 20.0, 0  ));
  rr3->SetPosition (Vector ( 40.0, 40.0, 0  ));
  rr4->SetPosition (Vector ( 70.0, 40.0, 0  ));
  rr5->SetPosition (Vector ( 40.0, 75.0, 0  ));
  rr6->SetPosition (Vector ( 70.0, 75.0, 0  ));

  anim.UpdateNodeDescription(0, "a");
  anim.UpdateNodeDescription(1, "b");
  anim.UpdateNodeDescription(2, "c");
  anim.UpdateNodeDescription(3, "d");
  anim.UpdateNodeDescription(4, "e");
  anim.UpdateNodeDescription(5, "f");
  anim.UpdateNodeDescription(6, "g");
  anim.UpdateNodeDescription(7, "h");
  anim.UpdateNodeDescription(8, "i");
  anim.UpdateNodeDescription(9, "j");
  anim.UpdateNodeDescription(10, "k");
  anim.UpdateNodeDescription(11, "r1");
  anim.UpdateNodeDescription(12, "r2");
  anim.UpdateNodeDescription(13, "r3");
  anim.UpdateNodeDescription(14, "r4");
  anim.UpdateNodeDescription(15, "r5");
  anim.UpdateNodeDescription(16, "r6");

   Simulator::Run ();
   Simulator::Destroy ();
   NS_LOG_INFO ("Done.");
 }
 

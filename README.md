# NS3-network-simulation

## Features
1) R1-R6 are routers and A-K are hosts
2) All links have a cost of 1, except the link R4-R5 has a cost 5
3) Assign IP addresses to each subnet connected to the router
4) Use RIP routing algorithm with Ipv4 and Poison Reverse as split horizon technique.
5) After 25 - sec, break the link between R3-R4.
6) Host A pings K and G pings H. Ping for 80 seconds and show the packet loss and average RTT in ms.
7) Run the simulation for 90 sec.

## Tracing
Use Pcap to find: 
1) Number of ICMP packets in pcap files of A ,G, H and K.
2) Number of ARP packets in pcap files of A ,G, H and K.
3) Print routing tables of all the routers at 10, 40 and 80 sec. 
4)  Observe major differences between the routing tables of R4 router generated at above mentioned times. 

## Visualization
1) Visualize the above simulation using NetAnim/PyViz in ns3. You will have to run the simulation during the demo. 
2) Paste a screenshot and report your observations of the simulation in your pdf.

NOTE:
The visualization is done using NetAnim

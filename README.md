# NS3-network-simulation

## Requirement
To create the given topology in NS3-network-simulator.
1) R1-R6 are routers and A-K are hosts
2) All links have a cost of 1, except the link R4-R5 has a cost 5
3) Assign IP addresses to each subnet connected to the router
4) Use RIP routing algorithm with Ipv4 and Poison Reverse as split horizon technique.
5) After 25 - sec, break the link between R3-R4.
6) Host A pings K and G pings H. Ping for 80 seconds and show the packet loss and average RTT in ms.
7) Run the simulation for 90 sec.


## Visualization
The above simulation can be visualized using NetAnim in ns3. The packet information can be extracted by running PCAP for the above network.


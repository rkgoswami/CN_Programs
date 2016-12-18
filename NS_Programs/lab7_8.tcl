#Step 1: Declare new Simulator
set ns [new Simulator]

#Step 2:Open the trace and nam file in write mode
set tf [open lab.tr w]
set nf [open lab.nam w]

#Step 3: Set Trace to ns
$ns trace-all $tf
$ns namtrace-all-wireless $nf 1000 1000

#Step 4: Set new topography
set topo [new Topography]
$topo load_flatgrid 1000 1000

#Step 5: Configure the node
$ns node-config -adhocRouting DSDV \
-llType LL \
-macType Mac/802_11 \
-ifqType Queue/DropTail \
-ifqLen 50 \
-phyType Phy/WirelessPhy \
-channelType Channel/WirelessChannel \
-propType Propagation/TwoRayGround \
-antType Antenna/OmniAntenna \
-topoInstance $topo \
-agentTrace ON \
-routerTrace ON  

#Step 6: Decide the topology

#	^
#	|								[sink2]
#  600 								[n2]	
#	|							  .'
#	|					        .'	
#	|					      .'
#	|					    .'
#	|					  .'
#	|					.'
#	|				  .'
#	|				.'
#  100			[n1]
#	|		  .'[sink1]	
#	|		.'	[tcp1]
#   50	[n0]	[ftp1]
#	|	[tcp0]
#	|	[ftp0]
#	|
#	|____50______100__________________600_________>


#Step 7: Create a god object
create-god 3

#Step 8: Create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

#Step 9: Locate the nodes on load_flatgrid
$n0 set X_ 50
$n0 set Y_ 50
$n0 set Z_ 0

$n1 set X_ 100
$n1 set Y_ 100
$n1 set Z_ 0

$n2 set X_ 600
$n2 set X_ 600
$n2 set Z_ 0

#Step 10: Declare the protocols
set tcp0 [new Agent/TCP]
set tcp1 [new Agent/TCP]
set sink1 [new Agent/TCPSink]
set sink2 [new Agent/TCPSink]

#Step 11: Attach these protocols to nodes
$ns attach-agent $n0 $tcp0
$ns attach-agent $n1 $tcp1
$ns attach-agent $n1 $sink1
$ns attach-agent $n2 $sink2

#Step 12: Declare the Application
set ftp0 [new Application/FTP]
set ftp1 [new Application/FTP]

#Step 13: Attach the Application to protocols
$ftp0 attach-agent $tcp0
$ftp1 attach-agent $tcp1

#Step 14: Connect the source to destination
$ns connect $tcp0 $sink1
$ns connect $tcp1 $sink2

#Write the proc function
proc finish { } {
	
	global ns tf nf
	$ns flush-trace
	exec nam lab.nam &
	close $nf
	close $tf

	set ctr 0
	set thr 0
	set fid [open lab.tr r]
	while {[gets $fid line]!=-1} {
		if {[string match "*s*" $line] && [string match "*AGT*" $line]} {
			set ctr [expr $ctr + 1]
		}
	}
	set thr [expr $ctr/5]
	puts "Number of packet transmitted: $ctr"
	puts "Throughput : $thr"
	exit 0
}
#Intial state
$ns at 0.1 "$n0 setdest 50 50 15"
$ns at 0.1 "$n1 setdest 100 100 25"
$ns at 0.1 "$n2 setdest 600 600 25"

#start the Application
$ns at 5 "$ftp0 start"
$ns at 5 "$ftp1 start"

#Node 1 move from node 0 at {50,50} to {550,550} near node 2 and start recieving packets from node 2
$ns at 20 "$n1 setdest 550 550 100"
#Return back to receiving packet from node 0
$ns at 30 "$n1 setdest 70 70 100"

$ns at 50 "finish"
$ns run




#Step 1: Declare a new simulator
set ns [new Simulator]

#Step 2: Open nam and trace file in write mode
set tf [open lab.tr w]
set nf [open lab.nam w]

#Step 3: Start the trace and nam
$ns trace-all $tf
$ns namtrace-all $nf

#Step 4: Decide the topology
		
#		[0]---------
#					|
#				   [2]----------[3]
#				    |
#		[1]---------

#Step 5: Declare the nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

#Step 6: Link the node 
$ns duplex-link $n0 $n2 100Mb 300ms DropTail 
$ns duplex-link $n1 $n2 100Mb 300ms DropTail
#less bandwidth to Link b/w n2 and n3 to drop the packets
$ns duplex-link $n2 $n3 1Mb 300ms DropTail	

#Step 7: Declare the protocol
set udp0 [new Agent/UDP]
set udp1 [new Agent/UDP]
set null3 [new Agent/Null]

#Step 8: Attach the protocol to nodes
$ns attach-agent $n0 $udp0
$ns attach-agent $n1 $udp1
$ns attach-agent $n3 $null3

#Step 9: Declare the application required
set cbr0 [new Application/Traffic/CBR]
set cbr1 [new Application/Traffic/CBR]

#Step 9: Attach the application to protocol
$cbr0 attach-agent $udp0
$cbr1 attach-agent $udp1

#Step 10: Set the queue-limit
$ns set queue-limit $n0 $n2 10
$ns set queue-limit $n1 $n2 10
$ns set queue-limit $n2 $n3 5


$udp0 set class_ 1
$udp1 set class_ 2
#Step 11: Setup Connection 
$ns connect $udp0 $null3
$ns connect $udp1 $null3

$cbr1 set packetSize_ 500Mb
$cbr1 set interval_ 0.005

#Step 12 : Write the proc function
proc finish { } {
global ns nf tf
$ns flush-trace 
exec nam lab.nam &
close $tf
close $nf
set ctr 0
set fid [open lab.tr r]
while {[gets $fid line] != 	-1} {
	if { [string match "*d*" $line] } {
		set ctr [expr $ctr + 1]
	}
}
puts "Numbers of packets dropped : $ctr"
exit 0
}

$ns at 0.1 "$cbr0 start"
$ns at 0.1 "$cbr1 start"
$ns at 5.0 "finish"
$ns run
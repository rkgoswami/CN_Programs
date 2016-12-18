#Step 1: Declare a new Simulator
set ns [new Simulator]

#Step 2: Open nam and trace file in write mode
set tf [open lab.tr w]
set nf [open lab.nam w]

#Step 3: Start the trace
$ns trace-all $tf
$ns namtrace-all $nf

#Step 4: Decide the topology
	   
#			   [cbr1]
#			   [udp1]							duplex-link
#	   [n0]	   [n1]	   [n2]	    [n3]-------------------------
#	 	|       |       |		 |							|
#	 	|       |       |		 |							|
#	-------------------------------------lan7				|
#														    |
#	-------------------------------------lan8				|
#		 	|         |           |		 					|
#	 		|         |           |		 					|
#	   	   [n4]	     [n5]	     [n6]------------------------	
#	   				[null5]

#Step 5: Create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

#Step 6: Create two lans
$ns make-lan "$n0 $n1 $n2 $n3" 100Mb 10ms LL Queue/DropTail Mac/802_3
$ns make-lan "$n4 $n5 $n6" 100Mb 10ms LL Queue/DropTail Mac/802_3

#Step 6: Setup Links
$ns duplex-link $n3 $n6 100Mb 10ms DropTail

#Step 6: Declare the protocols required
set udp1 [new Agent/UDP]
set null5 [new Agent/Null]

#Step 7: Attach the protocols to respective nodes
$ns attach-agent $n1 $udp1
$ns attach-agent $n5 $null5

#Step 8: Declare the application required
set cbr1 [new Application/Traffic/CBR]

#Step 9: Attach the application to respective node
$cbr1 attach-agent $udp1

#Step 10: Create error model
set err [new ErrorModel]
$ns lossmodel $err $n3 $n6
$err set rate_ 0.2

#Step 11: Connect the source and destination
$ns connect $udp1 $null5

#Step 12: Vary the packetSize and interval
$cbr1 set packetSize_ 1000Mb
$cbr1 set interval_ 0.0001

#Step 12: Write the proc funtion
proc finish { } {
	global ns nf tf
	$ns flush-trace
	exec nam lab.nam &
	close $nf
	close $tf

	set ctr 0
	set thr 0
	set fid [open lab.tr r]
	while {[gets $fid line]!=-1} {
		if {[string match "*8 5*" $line]} {
			set ctr [expr $ctr+1]
		}
	}
	set thr [expr $ctr/5]

	puts "Throughput : $thr"
	exit 0
}

$ns at 0.1 "$cbr1 start"
$ns at 5.0 "finish"
$ns run

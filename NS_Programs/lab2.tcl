#Step 1: Declare a new simulator
set ns [new Simulator]

#Step 2: Open nam and trace file in write mode
set nf [open lab.nam w]
set tf [open lab.tr w]

#Step 3: Start the trace 
$ns trace-all $tf
$ns namtrace-all $nf

#Step 4: Decide the topology

#		[ftp]
#		[tcp]-----------------------
#		[n0]---------			   |	
#					|			 [TCpSink]
#				   [n2]-----------[n3]
#			    	|			 [Null]
#		[n1]---------			   |  
#		[udp]-----------------------
#		[cbr]

#Step 5: Declare nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

#Step 6: Setup the link
$ns duplex-link $n0 $n2 100Mb 10ms DropTail
$ns duplex-link $n1 $n2 100Mb 10ms DropTail
$ns duplex-link $n2 $n3 100Mb 10ms DropTail

#Step 7: Declare the protocols
set tcp0 [new Agent/TCP]
set udp1 [new Agent/UDP]
set null3 [new Agent/Null]
set sink3 [new Agent/TCPSink]

#Step 8: Attach the protocols to nodes
$ns attach-agent $n0 $tcp0
$ns attach-agent $n1 $udp1
$ns attach-agent $n3 $sink3
$ns attach-agent $n3 $null3


#Step 9: Declare the application
set ftp0 [new Application/FTP]
set cbr1 [new Application/Traffic/CBR]

#Step 10: Attach the application to protocols
$ftp0 attach-agent $tcp0
$cbr1 attach-agent $udp1


#Step 11: Connect the source and destination
$ns connect $tcp0 $sink3
$ns connect $udp1 $null3
proc finish { } {
	global ns nf tf
	$ns flush-trace
	exec nam lab.nam &
	close $nf
	close $tf

	set tcpCtr 0
	set udpCtr 0
	set totCtr 0
	set fid [open lab.tr r]
	while {[gets $fid line] != -1} {
		set totCtr [expr $totCtr + 1]
		if {[string match "*tcp*" $line]} {
			set tcpCtr [expr $tcpCtr + 1]
		}
		if {[string match "*cbr*" $line]} {
			set udpCtr [expr $udpCtr + 1]
		}
	}
	puts "No. of TCP packets : $tcpCtr"
	puts "No. of UDP packets : $udpCtr"
	puts "Total No. of packets : $totCtr"
	exit 0
}
$ns at 0.1 "$ftp0 start"
$ns at 0.1 "$cbr1 start"
$ns at 5.0 "finish"
$ns run


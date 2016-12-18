#Step 1: Declare a new Simulator
set ns [new Simulator]

#Step 2: Open the trace and nam file in write mode
set tf [open lab.tr w]
set nf [open lab.nam w]

#Step 3: Start the trace file
$ns trace-all $tf
$ns namtrace-all $nf

#Step 4: Decide the topology [ 0 -> 2 ](udp) [1 -> 3](tcp) [2->1](tcp)

#		[udp]	[tcp][sink1]	  [null2][tcp]
#		[n0]		[n1]	      [n2]
#		 |       	 |             |
#		 |		 	 |		       |
#	---------------------------------- lan
#				|
#				|
#			   [n3]
#		   	  [sink3]

#Step 5: Create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

#Step 6: Create lan and setup the link
$ns make-lan -trace on "$n0 $n1 $n2 $n3" 10Mb 10ms LL Queue/DropTail Mac/802_3

#Step 7: Declare the required Protocols
set udp0 [new Agent/UDP]
set tcp1 [new Agent/TCP]
set tcp2 [new Agent/TCP]
set null2 [new Agent/Null]
set sink1 [new Agent/TCPSink]
set sink3 [new Agent/TCPSink]

#Step 8: Attach these Protocols to their respective nodes
$ns attach-agent $n0 $udp0
$ns attach-agent $n1 $tcp1
$ns attach-agent $n2 $tcp2

$ns attach-agent $n2 $null2
$ns attach-agent $n1 $sink1
$ns attach-agent $n3 $sink3

#Step 9: Declare the required Applications
set ftp1 [new Application/FTP]
set ftp2 [new Application/FTP]
set cbr0 [new Application/Traffic/CBR]

#Step 10: Attach the Application
$cbr0 attach-agent $udp0
$ftp1 attach-agent $tcp1
$ftp2 attach-agent $tcp2

#Step 11: Setup the connection
$ns connect $udp0 $null2
$ns connect $tcp1 $sink3
$ns connect $tcp2 $sink1

#Step 12: Set the interval
$cbr0 set interval_ 0.01
$ftp1 set interval_ 0.01
$ftp2 set interval_ 0.01

#Step 13: Write the proc function
proc finish { } {
	global ns nf tf
	$ns flush-trace
	exec nam lab.nam &
	close $nf
	close $tf
	set ctr 0
	set fid [open lab.tr r]
	while {[gets $fid line]!=-1} {
		if {[string match "c*" $line]} {
			set ctr [expr $ctr + 1]
		}
	}
	puts "No. of collision packets : $ctr"
	exit 0
}

$ns at 0.1 "$cbr0 start"
$ns at 1.2 "$ftp1 start"
$ns at 1.3 "$ftp2 start"
$ns at 5.0 "finish"
$ns run
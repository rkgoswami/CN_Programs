#Step 1: Declare new Simulator
set ns [new Simulator]

#Step 2: Open trace and nam file in write mode
set tf [open lab.tr w]
set nf [open lab.nam w]

#Step 3: Start the trace
$ns trace-all $tf
$ns namtrace-all $nf

#Step 4: Decided the topology
	
#	[ftp]
#	[tcp]------------------------->[sink0]
#	[n0]-------------	------------>[n3]
#					 | |
#				     [n2]
#				  	 | |
#	[n1]-------------	------------>[n4]	
#	[tcp]-------------------------->[sink1]
#	[telnet]

#Step 5: Declare the nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

#Step 6: Setup the link 
$ns duplex-link $n0 $n2 100Mb 10ms DropTail
$ns duplex-link $n1 $n2 100Mb 10ms DropTail
$ns duplex-link $n2 $n3 100Mb 10ms DropTail
$ns duplex-link $n2 $n4 100Mb 10ms DropTail

#Step 7: Declare the protocols
set tcp0 [new Agent/TCP]
set tcp1 [new Agent/TCP]
set sink3 [new Agent/TCPSink]
set sink4 [new Agent/TCPSink]

#Step 8: Setup/Attach the protocols to nodes
$ns attach-agent $n0 $tcp0
$ns attach-agent $n1 $tcp1
$ns attach-agent $n3 $sink3
$ns attach-agent $n4 $sink4

#Step 9: Declare the Applications
set ftp0 [new Application/FTP]
set tel1 [new Application/Telnet]

#Step 10: Attach the application to protocols
$ftp0 attach-agent $tcp0
$tel1 attach-agent $tcp1

#Step 11: Connect the source and destination
$ns connect $tcp0 $sink3
$ns connect $tcp1 $sink4

#Step 12: Vary the packet size and interval of telnet
$tel1 set packetSize_ 1000Mb
$tel1 set interval_ .0001

#Step 13: Write the proc function
proc finish { } {
	global ns nf tf
	$ns flush-trace

	exec nam lab.nam &
	close $nf
	close $tf

	set ctr0 0
	set ctr1 0
	set thr0 0
	set thr1 0
	set fid [open lab.tr r]
	while {[gets $fid line]!=-1} {
		if {[string match "*r*2 3*" $line]} {
			set ctr0 [expr $ctr0+1]
		}
		
		if {[string match "*r*2 4*" $line]} {
			set ctr1 [expr $ctr1+1]
		}
	}
	set thr0 [expr $ctr0/5]
	set thr1 [expr $ctr1/5]
	
	puts "No. of packet send by FTP: $ctr0"
	puts "Throughput for FTP : $thr0"
	puts "No. of packet send by FTP: $ctr0"
	puts "Throughput for TELNET : $thr1"
	exit 0
}

$ns at 0.1 "$ftp0 start"
$ns at 0.1 "$tel1 start"
$ns at 5.0 "finish"
$ns run


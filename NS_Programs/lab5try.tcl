set ns [new Simulator]
set nf [open lab.tr w]
set tf [open lab.nam w]

$ns trace-all $nf
$ns namtrace-all $tf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns make-lan -trace on "$n0 $n1 $n2 $n3" 10Mb 10ms LL Queue/DropTail Mac/802_3

set udp0 [new Agent/UDP]
set tcp1 [new Agent/TCP]
set tcp2 [new Agent/TCP]

set null2 [new Agent/Null]
set sink1 [new Agent/TCPSink]
set sink3 [new Agent/TCPSink]

set cbr0 [new Application/Traffic/CBR]
set ftp1 [new Application/FTP]
set ftp2 [new Application/FTP]

$ns attach-agent $n0 $udp0
$ns attach-agent $n1 $tcp1
$ns attach-agent $n2 $tcp2
$ns attach-agent $n2 $null2

$ns attach-agent $n1 $sink1
$ns attach-agent $n3 $sink3

$cbr0 attach-agent $udp0
$ftp1 attach-agent $tcp1
$ftp2 attach-agent $tcp2
$ns connect $udp0 $null2
$ns connect $tcp1 $sink3
$ns connect $tcp2 $sink1
$cbr0 set interval_ 0.01
$ftp1 set interval_ 0.01
$ftp2 set interval_ 0.01
proc finish {} {
	global ns nf tf
	$ns flush-trace
	exec nam lab.nam &
	close $tf
	close $nf
	set ctr0 0
	set fid [open lab.tr r]
	while {[gets $fid line] !=-1 } {
		if { [string match "c*" $line] } {
			set ctr0 [expr $ctr0 + 1]
		}
	}
	puts "No. of collision packets: $ctr0"
	exit 0
}
$ns at 0.1 "$cbr0 start"
$ns at 1.2 "$ftp1 start"
$ns at 1.3 "$ftp2 start"
$ns at 5.0 "finish"
$ns run
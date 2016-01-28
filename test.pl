#!/usr/bin/perl

#
# ./test.pl
# Run solver on a set of test puzzles and check the solution.
# Used to score solvers.
#

use strict;

my $SOLVER="./solvesudoku";
my $CHECKER="./sudokucheck.pl";
die "no $SOLVER found!" unless -e $SOLVER;

my $TIMEOUT = 30;  # time to solve each puzzle

my $PUZZLES="testpuzzles.txt";
$PUZZLES = $ARGV[0] if @ARGV >= 1;

open(my $fh, $PUZZLES) or die "$!\n";
my $n = 1;
while (<$fh>) {
    chomp;
    next unless /^[\.1-9]{81}$/;
    print "==="x3;
    print " puzzle $n ";
    print "==="x3, "\n";
    my $CMD = "echo '$_' | $SOLVER | $CHECKER";
    print "$CMD\n";
    # http://perldoc.perl.org/functions/alarm.html
    eval {  
	local $SIG{ALRM} = sub { die "alarm\n" }; # NB: \n required
        alarm $TIMEOUT;
	system("$CMD") == 0 or die "$!\n";
    };
    if ($@) {
        die unless $@ eq "alarm\n";   # FAIL
	die "timed out!\n";           # TIMEOUT
    }
    $n++;
}
close $fh;

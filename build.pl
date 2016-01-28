#!/usr/bin/perl

#
# ./build.pl
# First try build everying with warning as errors,
# Then rebuild for SPEED.
#

system("make clean") == 0 or die "$!\n";
system("make all") == 0 or die "$!\n";
system("make clean") == 0 or die "$!\n";
system("make all SPEED=1") == 0 or die "$!\n";

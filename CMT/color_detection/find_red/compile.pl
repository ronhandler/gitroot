#!/usr/bin/perl
#

print("Compiling project...\n");
system("g++ -std=c++11 Source.cpp ColorDetect.cpp `pkg-config --cflags --libs opencv` -o colordetect");

#!/usr/bin/perl
use File::Basename;
my $dir = dirname($0);

# This little script generates a png image using GraphViz dot tool,
# and then renders this image using feh.
system("$dir/a.out > $dir/temp.dot");
if ($? != 0) {
	print("some error occurred\n");
	exit();
}
system("dot -Tpng $dir/temp.dot > $dir/output.png");
system("feh $dir/output.png");
system("rm $dir/temp.dot");

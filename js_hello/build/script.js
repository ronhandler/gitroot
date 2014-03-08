///////////////////////////////////////////////
//                                           //
// This is a script that is parsed using v8. //
//                                           //
///////////////////////////////////////////////

// Include another js sciprt.
include('build/included.js');

function dbl(x) {
	return 2*x;
}

var str = "The value is: " + dbl(3) + '\n';
print(str);


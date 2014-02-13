///////////////////////////////////////////////
//                                           //
// This is a script that is parsed using v8. //
//                                           //
///////////////////////////////////////////////

// Include another js sciprt.
include('build/included.js');


function foo() {
	return 10;
}

(function () {
	var y=100;
})()


var str = "The value is: " + y*foo() + '\n';
print(str);


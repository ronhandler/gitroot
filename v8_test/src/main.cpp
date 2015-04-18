#include "main.h"

int main(int argc, char* argv[]) {
	V8_embed::ScriptEngine script;

	script.set("blah",
		[](int i)
		{
			std::cout << i << endl; 
		}
	);

	script.load("build/script.js");
	script.init();
	script.run();
	return 0;
}


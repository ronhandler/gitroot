#include <duktape.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string readfile(const char *filepath) {
	std::ifstream infile(filepath);
	std::string ret;
	std::string line;
	while (std::getline(infile, line)) {
		ret = ret + line + "\n";
	}
	return ret;
}

int main(int argc, char *argv[]) {
	duk_context *ctx = duk_create_heap_default();
	std::string script = readfile("script.js");
	duk_eval_string(ctx, script.c_str());
	duk_destroy_heap(ctx);
	return 0;
}


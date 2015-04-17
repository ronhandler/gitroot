#include "v8_embed.h"

string readfile(const char *filename)
{
	ifstream in(filename, ios::in | ios::binary);
	if (in) {
		string contents;
		in.seekg(0, ios::end);
		contents.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(-1);
}

Handle<Value> Include(const Arguments& args)
{
	// Get the param
    String::Utf8Value param1(args[0]->ToString());
	// Read the file passed by the param.
	string jsfile = readfile( string(*param1).c_str() );

	if(jsfile.length() > 0) {
		Handle<String> source = String::New(jsfile.c_str());
		Handle<Script> script = Script::Compile(source, String::New(string(*param1).c_str()));
		if (script.IsEmpty()) {
			return Undefined();
		}
		return script->Run();
	}

	// Undefined() is the JS equivalent of C++'s void return
	return Undefined();
}

Handle<Value> Print(const Arguments& args)
{
    v8::String::Utf8Value param1(args[0]->ToString());
	// Convert the param to string
	std::string msg = std::string(*param1);

	// Print it out.
	cout << msg;

	return Undefined();
}


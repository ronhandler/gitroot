#include "main.h"

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

static Handle<Value> Include(const Arguments& args)
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

static Handle<Value> Print(const Arguments& args)
{
    v8::String::Utf8Value param1(args[0]->ToString());
	// Convert the param to string
	std::string msg = std::string(*param1);

	// Print it out.
	cout << msg;

	return Undefined();
}

int main(int argc, char* argv[]) {

	try {
		// Read a script file into src_str.
		string src_fname,src_str;
		src_fname = "build/script.js";
		src_str = readfile(src_fname.c_str());

		// Create a stack-allocated handle scope.
		HandleScope handle_scope;
		Handle<ObjectTemplate> global_templ = ObjectTemplate::New();
		
		// Internal debugging methods to make development a little easier.
		global_templ->Set(String::New("print"), FunctionTemplate::New(Print));
		global_templ->Set(String::New("include"), FunctionTemplate::New(Include));
		
		// Create a new context.
		Persistent<Context> context = Context::New(0, global_templ);
		
		// Enter the created context for compiling and running our program.
		context->Enter();

		// Catch exceptions.
		TryCatch trycatch;

		// Create a string containing the JavaScript code to execute.
		Handle<String> source = String::New(src_str.c_str());
		
		// Compile the Javascript code.
		Handle<Script> script = Script::Compile(source, String::New(src_fname.c_str()));
		
		if (script.IsEmpty()) {
			//cerr << src_str << endl;
			context.Dispose();
			throw(-2);
		}

		// Run the script to get the result.
		Handle<Value> result = script->Run();
		
		// Check for errors.
		if (result.IsEmpty()) {
			Handle<Message> message = trycatch.Message();
			int linenum = message->GetLineNumber();
			cerr << 
					*String::AsciiValue(message->GetScriptResourceName()) << ":" <<
					linenum << ":" <<
					*String::AsciiValue(trycatch.Exception()) << ":" <<
					endl;
		}
		
		// Get rid of the persistent context.
		context.Dispose();

		// Convert the result to an ASCII string and print it.
		//String::AsciiValue ascii(result);
		//printf("%s\n", *ascii);

	}
	catch (int &i) {
		if (i==-1) {
			cerr << "Error reading file. Aborting." << endl;
			return i;
		} else
		if (i==-2) {
			cerr << "Error compiling script file. Aborting." << endl;
			return i;
		}
	}

	return 0;
}


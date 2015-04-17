#ifndef V8_EMBED_H
#define V8_EMBED_H

#include <iostream>
using namespace std;
#include <v8.h>
using namespace v8;
#include<functional>

// Used for reading a file into a string.
#include <fstream>
#include <string>
#include <cerrno>

string readfile(const char *filename);
Handle<Value> Include(const Arguments& args);
Handle<Value> Print(const Arguments& args);

namespace V8_embed {
	class ScriptEngine {
	private:
		string src_fname;
		Handle<ObjectTemplate> global_templ;
		// Create a stack-allocated handle scope.
		HandleScope handle_scope;
	public:
		ScriptEngine()
		{
			src_fname = "build/script.js";
			global_templ = ObjectTemplate::New();
		}
		template<typename Functor>
		void set(const string &func_name, Functor functor)
		{
			static string name = func_name;
			static auto f = functor;
			auto func = 
				[&](const Arguments& args) -> Handle<Value>
				{
					f(args[0]->ToInteger()->Value());
					return v8::Undefined();
				};
			global_templ->Set(String::New(func_name.c_str()), FunctionTemplate::New(func));
		}
		void load(const string &filename)
		{
			src_fname = filename;
		}
		int init()
		{
			try {
				// Read a script file into src_str.
				string src_str = readfile(src_fname.c_str());
				
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
					cerr << "Error reading file " << src_fname << ". Aborting." << endl;
					return i;
				} else
				if (i==-2) {
					cerr << "Error compiling script file. Aborting." << endl;
					return i;
				}
			}
			return 1;
		}
	};
}

#endif


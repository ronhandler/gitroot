#ifndef MAIN_H
#define MAIN_H

#include <v8.h>
using namespace v8;
#include <iostream>
using namespace std;

// Used for reading a file into a string.
#include <fstream>
#include <string>
#include <cerrno>

string readfile(const char *filename);
static Handle<Value> Include(const Arguments& args);
static Handle<Value> Print(const Arguments& args);

#endif


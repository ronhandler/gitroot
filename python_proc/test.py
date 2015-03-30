#!/usr/bin/python

import sys
import proc

if __name__ == "__main__":
    string,_ = proc.call("echo hello world")
    print(string)
    sys.exit(0);


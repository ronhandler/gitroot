#!/usr/bin/python -B

import sys
import proc

if __name__ == "__main__":
    string,_ = proc.call("""for i in `seq 1 10`; do echo $i; done""")
    print(string)
    sys.exit(0);


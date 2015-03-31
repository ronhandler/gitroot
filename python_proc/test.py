#!/usr/bin/python3 -B

import sys
import proc

if __name__ == "__main__":

    cmds = [
        ("sleep 1;echo hello world",None),
        ("echo hi there",2),
    ]

    with proc.MyPool(processes=4) as pool:
        results = pool.starmap(proc.call, cmds)
        for i in results:
            print(i)

    sys.exit(0);


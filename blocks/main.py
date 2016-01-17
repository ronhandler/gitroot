#!/usr/bin/python3

import os
import sys

from blocksgame import *

def main():

    if len(sys.argv) != 3:
        usage = ("Usage: " + os.path.basename(__file__) + " <INIT_STATE> <GOAL_STATE>\n"
                 "Play the game \"Blocks\" in which the computer will try to arrange the blocks in\n"
                 "INIT_STATE to match the blocks in GOAL_STATE.\n"
                 "\n"
                 "State structure:\n"
                 "  Each one of the states should adhere to the following structure:\n"
                 "    * Consist of one string.\n"
                 "    * Consist of unique alphabet characters and commas only.\n"
                 "    * Consist of at least one comma.\n"
                 "    * Both states should consist of the same alphabet characters, but in different order.\n"
                 "    * Both states should have the same number of commas.\n"
                 "\n"
                 "  Example:\n"
                 "    Start a Blocks game with the following structure:\n"
                 "      b             c  \n"
                 "      a c         a b  \n"
                 "      = = =     = = =  \n"
                 "      1 2 3     1 2 3  \n"
                 "    # " + os.path.basename(__file__) + " ab,c, ,a,bc\n"
                )
        print(usage)
        sys.exit(0)

    initstate = sys.argv[1].split(",")
    goalstate = sys.argv[2].split(",")

    if len(initstate) < 2:
        print("Each state should have at least two columns.", file=sys.stderr)
        sys.exit(1)

    if len(initstate) != len(goalstate):
        print("Both states should have the same number of columns.", file=sys.stderr)
        sys.exit(1)

    if sorted("".join(initstate)) != sorted("".join(goalstate)):
        print("Both states should consist of the same alphabet characters.", file=sys.stderr)
        sys.exit(1)

    if "".join(initstate).isalpha() is False or "".join(goalstate).isalpha() is False:
        print("Both states should consist of alphabet characters and commas only.", file=sys.stderr)
        sys.exit(1)

    if len(set("".join(initstate))) != len("".join(initstate)):
        print("The alphabet characters in both states should be unique.", file=sys.stderr)
        sys.exit(1)

    game = Blocksgame(initstate, goalstate)
    game.play()

if __name__ == "__main__":
    main()

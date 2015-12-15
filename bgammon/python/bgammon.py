#!/usr/bin/python3

from copy import deepcopy
from gamestate import *
from rules import *
from gameai import *

def playGame1():

    # Create the rules class.
    rules = Rules()

    # Create a minmax tree with the initial game state.
    minmaxTree = Node()
    minmaxTree.state = GameState()

    ai = GameAI()
    val = ai.minmax(minmaxTree, 1, True)
    print("Minmax returned: " + str(val))

    print(minmaxTree.state)
    minmaxTree.state.movePiece(18, 2)
    print(minmaxTree.state)


    #nextstates = rules.getNextStates(minmaxTree.state)
    #print("Number of next states: " + str(len(nextstates)))


if __name__ == '__main__':
    playGame1()


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

    nextstates = rules.getNextStates(minmaxTree.state)
    for s in nextstates:
        minmaxTree.addChild(s)

    ai = GameAI()
    (val,node) = ai.minmax(minmaxTree, 3, True)

    print("Minmax returned: " + str(val))
    print(node.state)

    #print(minmaxTree.state)
    #minmaxTree.state.movePiece(23, 3)
    #minmaxTree.state.removeFromBar(19)

    #print("Number of next states: " + str(len(nextstates)))


if __name__ == '__main__':
    playGame1()


#!/usr/bin/python3

from definitions import *
from gamestate import *
from dice import *

class Rules:
    def __init__(self):
        pass

    def getNextStates(self, state):
        # Create an empty state list that will eventually be returned.
        statelist = []

        # TODO: Finish up the function...
        newstate = GameState()
        newstate.movePiece(23,3)
        statelist.append(newstate)

        return statelist


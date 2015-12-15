#!/usr/bin/python3

from definitions import *
from gamestate import *
from dice import *
import math

class Node:
    def __init__(self, state=None):
        self.state = None
        self.parent = None
        self.children = None
        if isinstance(state, GameState):
            self.state = state


class GameAI(object):
    def __init__(self):
        pass

    def minmax(self, node, depth, maximizingPlayer):
        # If reached max depth, or reached a terminal node, return h.
        if depth == 0 or not node.children:
            return node.state.heuristics()

        # Init maximizing player's bestValue:
        bestValue = float('-inf')
        if not maximizingPlayer:
            # Init minimizing player's bestValue:
            bestValue = float('inf')

        # For each child, return the minmax recursion result.
        for child in node.children:
            val = minmax(child, depth-1, not maximizingPlayer)
            if maximizingPlayer:
                bestValue = max(bestValue, val)
            else:
                bestValue = min(bestValue, val)

        return bestValue



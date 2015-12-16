#!/usr/bin/python3

from definitions import *
from gamestate import *
from dice import *
import math

class Node:
    def __init__(self, state=None):
        self.state = None
        self.parent = None
        self.children = []
        if isinstance(state, GameState):
            self.state = state

    def addChild(self, state):
        node = Node(state)
        node.parent = self
        self.children.append(node)

class GameAI(object):
    def __init__(self):
        pass

    def minmax(self, node, depth, maximizingPlayer):
        # If reached max depth, or reached a terminal node, return h.
        if depth == 0 or not node.children:
            return (node.state.heuristics(), node)

        # Init maximizing player's bestValue:
        bestValue = float('-inf')
        if not maximizingPlayer:
            # Init minimizing player's bestValue:
            bestValue = float('inf')

        # For each child, return the minmax recursion result.
        retnode = None
        for child in node.children:
            # TODO: remove switch if not needed.
            child.state.switch()
            (val,nextnode) = self.minmax(child, depth-1, not maximizingPlayer)
            if maximizingPlayer:
                if bestValue < val:
                    retnode = nextnode
                bestValue = max(bestValue, val)
            else:
                if bestValue > val:
                    retnode = nextnode
                bestValue = min(bestValue, val)

        return (bestValue,retnode)



from state import *

class Blocksgame:

    def __init__(self, initstate, goalstate):
        self.initstate = State(initstate)
        self.goalstate = State(goalstate)

    def play(self):
        print("Initial state: ")
        print(self.initstate)
        print("")
        print("Goal state: ")
        print(self.goalstate)
        pass

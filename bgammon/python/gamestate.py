#!/usr/bin/python

class GameState(object):
    WHITE = 0
    BLACK = 1
    def __init__(self):
        self.__board = [0]*24
        self.__bar = [0]*2
        self.__bar[self.BLACK] = 2

        self.__color = self.WHITE

        self.__board[23] = -2
        self.__board[12] = -5
        self.__board[7] = -3
        self.__board[5] = -5

        self.__board[18] = 5
        self.__board[16] = 3
        self.__board[11] = 5
        self.__board[0] = 2

    # This function returns a string of the formatted board.
    def __str__(self):
        print_list = (
            # First row
            self.__board[11:5:-1] +
            [self.__bar[self.WHITE]] +
            self.__board[5::-1] +
            # Second row
            self.__board[12:18] +
            [self.__bar[self.BLACK]] +
            self.__board[18:]
        )
        fmt = ("# " + "% d "*6 + "|%0.2d| " + "% d "*6 + "#\n")*2
        return fmt % tuple(print_list)

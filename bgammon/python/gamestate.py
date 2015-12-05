#!/usr/bin/python3

from definitions import *

class GameState(object):
    def __init__(self):
        self.__board = [0]*24
        self.__bar = [0]*2

        self.__color = Color.BLACK

        self.__board[23] = -2
        self.__board[12] = -5
        self.__board[7] = -3
        self.__board[5] = -5

        self.__board[18] = 5
        self.__board[16] = 3
        self.__board[11] = 5
        self.__board[0] = 2

    def switch(self):
        if self.__color == Color.BLACK:
            self.__color = Color.WHITE
        else:
            self.__color = Color.BLACK

    # This function returns a string of the formatted board.
    def __str__(self):
        ascii_board = [
            " 13 14 15 16 17 18       19 20 21 22 23 24  \n",
            "+------------------------------------------+\n",
            "| .  .  .  .  .  . |   |  .  .  .  .  .  . |\n",
            "|                  |   |                   |\n",
            "|                  |   |                   |\n",
            "|                  |   |                   |\n",
            "|                  |   |                   |\n",
            "|                  |BAR|                   |\n",
            "|                  |   |                   |\n",
            "|                  |   |                   |\n",
            "|                  |   |                   |\n",
            "|                  |   |                   |\n",
            "| .  .  .  .  .  . |   |  .  .  .  .  .  . |\n",
            "+------------------------------------------+\n",
            " 12 11 10  9  8  7        6  5  4  3  2  1  \n"
        ]

        # Convert str-list to list-of-list.
        ascii_list = list()
        for row in ascii_board:
            ascii_list.append(list(row))

        for i in range(12,18):
            index = i*3-36+2
            if self.__board[i] > 0:
                ascii_list[2][index] = "o"
            elif self.__board[i] < 0:
                ascii_list[2][index] = "x"

        # Convert list-of-list to str.
        buff = ""
        for row in ascii_list:
            buff = buff + ("".join(row))
        return buff

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

        def __draw_col(x, size, direction):
            start = 0
            if direction == 1:
                start = 2
            else:
                start = 12

            color = "."
            if size < 0:
                color = "o"
                size = size * -1
            elif size > 0:
                color = "#"

            if size > 5:
                ascii_list[start][x] = str(size);
                if size > 9:
                    ascii_list[start][x+1] = "";
                start = start + direction
                size = 4
            while size>0:
                ascii_list[start][x] = color;
                start = start + direction
                size = size-1

        for i in range(12,18):
            index = i*3-36+2
            __draw_col(index, self.__board[i], 1)
            __draw_col(index, self.__board[23-i], -1)
        for i in range(18,24):
            index = i*3-36+8
            __draw_col(index, self.__board[i], 1)
            __draw_col(index, self.__board[23-i], -1)

        # Convert list-of-list to str.
        buff = ""
        for row in ascii_list:
            buff = buff + ("".join(row))
        return buff

#!/usr/bin/python3

from definitions import *
from dice import *

class GameState(object):
    def __init__(self):
        self.__dicelist = [[],[]]
        for d in range(0,2):
            for i in range(0,6):
                for j in range(0,6):
                    self.__dicelist[d].append(Dice(i+1,j+1))
            for i in range(0,10):
                self.__dicelist[d].append(Dice())

        self.__board = [0]*24
        self.__bar = [0]*2

        self.__player = Player.CURRENT
        #self.__player = Player.OPPONENT

        self.__board[23] = 2
        self.__board[12] = 5
        self.__board[7] = 3
        self.__board[5] = 5

        self.__board[18] = -5
        self.__board[16] = -3
        self.__board[11] = -5
        self.__board[0] = -2

    def getAmount(self, src):
        return self.__board[src]

    def isEnemy(self, src):
        return (self.__board[src] < 0)

    def isBarEmpty(self):
        return (len(self.__bar[0]) == 0)

    def getPlayerAmount(self, src):
        val = self.getAmount(src)
        if val < 0:
            return -val
        else:
            return val

    def removeFromBar(self, dst):
        if self.__bar[0] == 0:
            return
        if dst < 18 or dst >= 24:
            return
        if self.getAmount(dst) < -1:
            return
        if self.getAmount(dst) == -1:
            self.__bar[0] -= 1
            self.__board[dst] = 1
            self.__bar[1] += 1
            return
        else:
            self.__bar[0] -= 1
            self.__board[dst] += 1

    def movePiece(self, src, amount):

        dst = src - amount

        # If src is empty or enemy, can't move.
        if self.getAmount(src) < 1:
            return

        # Boundaries check.
        if src >= 24 or dst < 0:
            return


        # Enemy check:
        if self.isEnemy(dst):
            if self.getAmount(dst) < -1:
                # What happens when can't eat enemy.
                return
            elif self.getAmount(dst) == -1:
                # What happens when an enemy piece is eaten.
                self.__board[src] -= 1
                self.__board[dst] = 1
                self.__bar[1] += 1
                return

        self.__board[src] -= 1
        self.__board[dst] += 1
        
                
    def switch(self):
        # Swap players.
        if self.__player == Player.OPPONENT:
            self.__player = Player.CURRENT
        else:
            self.__player = Player.OPPONENT

        i = 12
        j = 11
        while i<24:
            # Swap board.
            temp = self.__board[i]
            self.__board[i] = -self.__board[j]
            self.__board[j] = -temp
            i += 1
            j -= 1

        # Swap dice list.
        temp = self.__dicelist[0]
        self.__dicelist[0] = self.__dicelist[1]
        self.__dicelist[1] = temp

        # Swap bar list.
        temp = self.__bar[0]
        self.__bar[0] = self.__bar[1]
        self.__bar[1] = temp


    def heuristics(self):
        # Evaluate the heuristics value for a specific state

        counter = 0
        for i in range(0,24):
            val = self.getAmount(i)
            if val > 0:
                counter = counter + (24-i) * val
        return counter


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
                color = "-"
                size = size * -1
            elif size > 0:
                color = "+"

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
        # Drawing the pieces on the bar.
        __draw_col(21, self.__bar[0], 1)
        __draw_col(21, self.__bar[1], -1)

        # Convert list-of-list to str.
        buff = ""
        for row in ascii_list:
            buff = buff + ("".join(row))

        # Add the dice lists:
        buff = buff + "\n" + "Dice: " + str(self.__dicelist[0])
        buff = buff + "\n" + "Dice: " + str(self.__dicelist[1])
        return buff

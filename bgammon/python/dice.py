#!/usr/bin/python3

from definitions import *
from random import randint

class Dice:
    def __init__(self, a=None, b=None):
        self.__a = a
        self.__b = b
        if a==None:
            self.__a = randint(1,6)
        if b==None:
            self.__b = randint(1,6)

    def isDouble(self):
        return (self.__a == self.__b)

    def getMoves(self):
        if isDouble is True:
            return [self.__a, self.__a, self.__a, self.__a]
        else:
            return [self.__a, self.__b]

    def __str__(self):
        return "" + str(self.__a) + "+" + str(self.__b) + ""
    def __repr__(self):
        return str(self)

#!/usr/bin/python

import curses
import time
import threading

xpos = 0
ypos = 0

def main_loop(screen):
    while 1:
        screen.clear()
        screen.refresh()
        screen.addstr(ypos, xpos, "Hello world\n")
        screen.refresh()
        time.sleep(0.05)

screen = curses.initscr()
curses.noecho()
curses.curs_set(0)
screen.keypad(1)

thread = threading.Thread(target=main_loop, args=(screen,))
thread.daemon = True
thread.start()

# Key handling loop.
while 1:
    event = screen.getch()
    if event == ord("q"):
        break
    if event == ord("w"):
        ypos = ypos-1
    if event == ord("a"):
        xpos = xpos-1
    if event == ord("s"):
        ypos = ypos+1
    if event == ord("d"):
        xpos = xpos+1
    if xpos<0: xpos=0
    if ypos<0: ypos=0
    maxy,maxx = screen.getmaxyx()
    if xpos>maxx-1: xpos=maxx-1
    if ypos>maxy-2: ypos=maxy-2

curses.endwin()

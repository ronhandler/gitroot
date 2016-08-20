#!/usr/bin/python

from time import sleep
from enum import Enum
import glfw
from OpenGL.GL import *

class Dir(Enum):
    up = 1
    down = 2
    left = 3
    right = 4
    empty = 5

class Player:
    def __init__(self):
        self.alive = True
        self.pos = (5,5)
        self.next = None
        self.lastDir = Dir.left
        self.grow_count = 25
        pass
    def move(self, x, y):
        old_pos = self.pos
        self.pos = (x, y)
        if self.next is not None:
            self.next.move(old_pos[0], old_pos[1])
    def grow(self, x, y):
        old_pos = self.pos
        self.pos = (x, y)
        if self.next is not None:
            self.next.grow(old_pos[0], old_pos[1])
        else:
            tail = Player()
            tail.pos = old_pos
            self.next = tail
    def checkClear(self, x, y):
        if self.pos[0] == x and self.pos[1] == y:
            return False
        if self.next is None:
            return True
        else:
            return self.next.checkClear(x,y)

    def play(self, d=Dir.empty):
        if d == Dir.empty:
            d = self.lastDir

        if self.grow_count > 0:
            self.grow_count = self.grow_count - 1
            func = self.grow
        else:
            func = self.move

        x = 0
        y = 0
        if d == Dir.up:
            x = self.pos[0]
            y = self.pos[1]-1
        elif d == Dir.down:
            x = self.pos[0]
            y = self.pos[1]+1
        elif d == Dir.left:
            x = self.pos[0]-1
            y = self.pos[1]
        elif d == Dir.right:
            x = self.pos[0]+1
            y = self.pos[1]
        
        # Check if game is over.
        if self.checkClear(x,y) is False:
            self.alive = False

        func(x, y)

    def draw(self):
        size = 0.02
        x = self.pos[0]*size*2
        y = -self.pos[1]*size*2
        glColor3f(1, 1, 1)
        glBegin(GL_QUADS)
        glVertex3f(x-size, y-size, 0)
        glVertex3f(x-size, y+size, 0)
        glVertex3f(x+size, y+size, 0)
        glVertex3f(x+size, y-size, 0)
        glEnd()
        if self.next is not None:
            self.next.draw()

class App:
    def key_callback(self, window, key, scancode, action, mods):
        if action == glfw.PRESS and key == glfw.KEY_ESCAPE:
            self.run = False
            return
        if action == glfw.PRESS and key == glfw.KEY_LEFT:
            if self.dir is not Dir.right:
                self.dir = Dir.left
        if action == glfw.PRESS and key == glfw.KEY_RIGHT:
            if self.dir is not Dir.left:
                self.dir = Dir.right
        if action == glfw.PRESS and key == glfw.KEY_UP:
            if self.dir is not Dir.down:
                self.dir = Dir.up
        if action == glfw.PRESS and key == glfw.KEY_DOWN:
            if self.dir is not Dir.up:
                self.dir = Dir.down

    def draw(self):
        glClear(GL_COLOR_BUFFER_BIT)
        if self.snake.alive is False:
            glClearColor(1, 0, 0, 0)
            glClear(GL_COLOR_BUFFER_BIT)
        else:
            self.snake.draw()

    def __init__(self):

        self.dir = Dir.empty
        self.run = True
        self.snake = Player()

        if not glfw.init():
            return
        self.window = glfw.create_window(400, 300, "Hello, World!", None, None)
        if not self.window:
            glfw.terminate()
            return
        glfw.make_context_current(self.window)
        glfw.set_key_callback(self.window, self.key_callback)

        while self.run and not glfw.window_should_close(self.window):

            # Update player's position
            self.snake.play(self.dir)
            sleep(0.075)

            self.draw()
            glfw.swap_buffers(self.window)
            glfw.poll_events()

            if self.snake.alive is False:
                sleep(1.075)
                self.run = False
                
        glfw.terminate()

if __name__ == '__main__':
    app = App()

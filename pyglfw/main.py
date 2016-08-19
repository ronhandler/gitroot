#!/usr/bin/python

import glfw
from OpenGL.GL import *

class App:

    def key_callback(self, window, key, scancode, action, mods):
        if action == glfw.PRESS and key == glfw.KEY_ESCAPE:
            self.run = False
            return

    def draw(self):
        pos = 0.5
        glClear(GL_COLOR_BUFFER_BIT)
        glBegin(GL_QUADS)
        glColor3f(1, 1, 1)
        glVertex3f(-pos, -pos, 0)
        glVertex3f(-pos,  pos, 0)
        glVertex3f( pos,  pos, 0)
        glVertex3f( pos, -pos, 0)
        glEnd()

    def __init__(self):

        self.run = True

        if not glfw.init():
            return
        self.window = glfw.create_window(400, 300, "Hello, World!", None, None)
        if not self.window:
            glfw.terminate()
            return
        glfw.make_context_current(self.window)
        glfw.set_key_callback(self.window, self.key_callback)

        while self.run and not glfw.window_should_close(self.window):
            self.draw()
            glfw.swap_buffers(self.window)
            glfw.poll_events()

        glfw.terminate()

if __name__ == '__main__':
    app = App()

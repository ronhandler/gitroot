#!/usr/bin/python3 -B
from functools import partial
from multiprocessing.dummy import Pool
import subprocess
import threading

class Command(object):
    def __init__(self, cmd):
        self.out = None
        self.cmd = cmd
        self.process = None

    def run(self, timeout=None):
        def target():
            self.process = subprocess.Popen(self.cmd, shell=True, stdout=subprocess.PIPE)
            self.out = self.process.communicate()[0].decode('utf-8').strip()

        thread = threading.Thread(target=target)
        thread.daemon = True
        thread.start()

        thread.join(timeout)
        if thread.is_alive():
            # Terminating process because of timeout.
            #self.process.terminate()
            self.process.kill()
            thread.join()
            return "", -1

        return self.out,self.process.returncode


def wrapper(cmd, timeout=None):
    command = Command(cmd)
    return command.run(timeout)

commands = [
    'echo "Starting proc 1"; sleep 1; echo "Done!"',
    'echo "Starting proc 2"; sleep 1; echo "Done!"',
    'echo "Starting proc 3"; sleep 1; echo "Done!"',
    'echo "Starting proc 4"; sleep 6; echo "Done!"',
]

pool = Pool(5) # two concurrent commands at a time
for out,ret in pool.imap(partial(wrapper, timeout=2), commands):
    print(str(ret) + ": " + out)
    pass


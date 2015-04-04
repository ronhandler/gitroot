#!/usr/bin/python3 -B
import threading
from threading import Timer
from functools import partial
from multiprocessing.dummy import Pool
from subprocess import call

commands = [
    'echo "Starting proc 1"; sleep 1; echo "Done!"',
    'echo "Starting proc 2"; sleep 1; echo "Done!"',
    'echo "Starting proc 3"; sleep 1; echo "Done!"',
    'echo "Starting proc 4"; sleep 1; echo "Done!"',
]

pool = Pool(2) # two concurrent commands at a time
for i, returncode in enumerate(pool.imap(partial(call, shell=True, timeout=2), commands)):
    if returncode != 0:
       print("%d command failed: %d" % (i, returncode))


#!/usr/bin/python -B
#
# This python module is a wrapper around subprocess.
# Features:
#   - Capture output from command.
#   - Capture return value from command.
#   - Optional timeout in seconds. After timeout is met, an exception will be
#     thrown.
#
#===========================================================================

import sys
import subprocess
import signal

# Tries to run a process, but times out after some time.
def call_command(args, timeout=0, exception=False):
    proc = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    try:
        signal.signal(signal.SIGALRM, alarm_handler)
        signal.alarm(timeout)  # Default timeout is 60 seconds.
        result = proc.communicate()[0].decode('utf-8').strip()
        signal.alarm(0)  # Reset the alarm.
        return result, proc.returncode
    except Alarm:
        # If the process timed out, kill it.
        proc.kill()
        if exception == True:
            raise Alarm("Execution timed out after " + str(timeout) + " seconds.  Command: " + args)
        else:
            return ("", -1)

class Alarm(Exception):
    pass

def alarm_handler(signum, frame):
    raise Alarm

import multiprocessing
import multiprocessing.pool

class NoDaemonProcess(multiprocessing.Process):
    # make 'daemon' attribute always return False
    def _get_daemon(self):
        return False
    def _set_daemon(self, value):
        pass
    daemon = property(_get_daemon, _set_daemon)

# We sub-class multiprocessing.pool.Pool instead of multiprocessing.Pool
# because the latter is only a wrapper function, not a proper class.
class MyPool(multiprocessing.pool.Pool):
    Process = NoDaemonProcess

def wrapper(cmd, timeout=None):
    with multiprocessing.Pool(processes=1) as pool:
        try:
            result = []
            r = pool.map_async(call_command, [cmd], callback=result.append)
            r.get(timeout)
            return result[0][0]
        except multiprocessing.TimeoutError:
            return (None,-1)

def call(cmd, timeout=None):
    return wrapper(cmd,timeout)


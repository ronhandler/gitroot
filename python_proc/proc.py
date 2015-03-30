#!/usr/bin/python
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
def call(args, timeout=0):
	proc = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
	try:
		signal.signal(signal.SIGALRM, alarm_handler)
		signal.alarm(timeout)  # Default timeout is 60 seconds.
		result = proc.communicate()[0].strip().decode('utf-8')
		signal.alarm(0)  # Reset the alarm.
	except Alarm:
		# If the process timed out, kill it.
		proc.kill()
		raise Alarm("Execution timed out after " + str(timeout) + " seconds.  Command: " + args)
	return result, proc.returncode

class Alarm(Exception):
	pass

def alarm_handler(signum, frame):
	raise Alarm

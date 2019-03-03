from __future__ import print_function

import os

from comfortable_swipe import autostart
from comfortable_swipe.cpp import service
from comfortable_swipe.constants import NAME, exe

def print_status():
  service.status()
  print('autostart is', autostart.get_status().upper())
  print('{} is {}'.format(NAME, 'RUNNING' if is_running() else 'STOPPED'))


def is_running():
  import psutil
  for process in psutil.process_iter():
    process_args = [process.name()] + process.cmdline()
    for index in range(len(process_args) - 1):
      if process_args[index + 1] == 'start' and process_args[index].endswith(NAME):
        return True
  return False

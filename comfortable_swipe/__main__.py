from __future__ import print_function

import sys

from comfortable_swipe.autostart import toggle_status
from comfortable_swipe.constants import CONFIG
from comfortable_swipe.status import print_status

from comfortable_swipe.cpp import service as cpp_service

def main():
  if len(sys.argv) <= 1:
    cpp_service.help()
  else:
    dict(
      start=cpp_service.start,
      stop=cpp_service.stop,
      restart=cpp_service.restart,
      buffer=cpp_service.buffer,
      help=cpp_service.help,
      debug=cpp_service.debug,
      status=print_status,
      autostart=lambda: print('Autostart switched', toggle_status()),
      config=lambda: print(CONFIG),
    )[sys.argv[1]]()

if __name__ == '__main__':
  main()

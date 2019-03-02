from __future__ import print_function

import sys
from comfortable_swipe import service

if len(sys.argv) <= 1:
  service.help()
else:
  dict(
    start=service.start,
    stop=service.stop,
    restart=service.restart,
    autostart=service.autostart,
    buffer=service.buffer,
    help=service.help,
    config=service.config,
    debug=service.debug,
    status=service.status
  )[sys.argv[1]]()

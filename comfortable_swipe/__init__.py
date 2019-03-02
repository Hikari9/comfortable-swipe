import sys
from comfortable_swipe import service

def main():
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

if __name__ == '__main__':
  main()

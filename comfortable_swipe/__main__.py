import sys
from comfortable_swipe import service
from comfortable_swipe.cpp import service as cpp_service

def main():
  if len(sys.argv) <= 1:
    service.help()
  else:
    dict(
      start=cpp_service.start,
      stop=cpp_service.stop,
      restart=cpp_service.restart,
      autostart=service.autostart,
      buffer=cpp_service.buffer,
      help=cpp_service.help,
      config=cpp_service.config,
      debug=cpp_service.debug,
      status=cpp_service.status
    )[sys.argv[1]]()

if __name__ == '__main__':
  main()

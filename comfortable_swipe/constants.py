import os
import sys

from distutils.spawn import find_executable


NAME = 'comfortable-swipe'
DESCRIPTION = 'Comfortable 3-finger and 4-finger swipe gestures'
BIN = os.path.dirname(sys.executable)
DIR = os.path.dirname(os.path.abspath(__file__))
PYTHON_NAME = os.path.basename(DIR)
RES = os.path.join(DIR, 'res')
CONFIG = os.path.join(sys.prefix, 'local', 'share', NAME, '{}.conf'.format(NAME))
DEFAULT_CONFIG = os.path.join(RES, 'defaults.conf')

def exe():
  return find_executable(NAME)

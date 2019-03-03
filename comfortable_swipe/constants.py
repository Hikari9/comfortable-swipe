import os
import sys


EXE = 'comfortable-swipe'
DIR = os.path.dirname(os.path.abspath(__file__))
RES = os.path.join(DIR, 'res')
CONFIG = os.path.join(sys.prefix, 'local', 'share', EXE, EXE + '.conf')
DEFAULT_CONFIG = os.path.join(RES, 'defaults.conf')

from __future__ import print_function

import os
from comfortable_swipe.util import autostart_path, autostart_template

def autostart():
  autostart = autostart_path()
  if os.path.exists(autostart):
    os.remove(autostart)
    print('Autostart switched off')
  else:
    with open(autostart, 'w') as file:
      file.write(autostart_template())
    print('Autostart switched on')

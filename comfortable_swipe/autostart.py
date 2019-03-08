from __future__ import print_function

import os
import sys

from comfortable_swipe.constants import NAME, RES, exe


# status enums
OFF = 'off'
ON = 'on'


# the target path to the autostart desktop file
def target_path():
  return os.path.join(
    os.getenv(
      'XDG_CONFIG_HOME',
      os.path.join(os.getenv('HOME'), '.config')
    ),
    'autostart',
    '{}.desktop'.format(NAME)
  )


# path to the autostart template file to be copied
def template_path():
  return os.path.join(RES, '{}.desktop'.format(NAME))


# parsed contents of the template file
def template(raw=False):
  with open(template_path(), 'r') as file:
    contents = file.read()
  if raw:
    return contents
  return contents.replace('Exec=' + NAME, 'Exec={} {}'.format(sys.executable, exe()))


# gets the current autostart status
def get_status():
  return ON if os.path.exists(target_path()) else OFF


# sets the autostart status
def set_status(status=ON):
  if status == ON:
    # make sure dir exists
    path = target_path()
    path_dir = os.path.dirname(path)
    if not os.path.exists(path_dir):
      os.makedirs(path_dir)
    with open(target_path(), 'w') as file:
      file.write(template())
  elif status == OFF:
    if os.path.exists(target_path()):
      os.remove(target_path())
  else:
    raise ValueError('invalid status for autostart')

  return status


# toggles autostart status
def toggle_status():
  return set_status(OFF if get_status() == ON else ON)

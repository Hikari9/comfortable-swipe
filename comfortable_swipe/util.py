import os

from distutils.spawn import find_executable

__EXE__ = 'comfortable-swipe'
__DIR__ = os.path.dirname(__file__)
__RES__ = os.path.join(__DIR__, 'res')


def conf_filename():
  return os.path.join(sys.prefix, 'local', 'share', __EXE__, __EXE__ + '.conf')


def autostart_path():
  return os.path.join(
    os.getenv('XDG_CONFIG_HOME', os.path.join(os.getenv('HOME'), '.config')),
    'autostart',
    __EXE__ + '.desktop'
  )


def autostart_template():
  autostart_template_filename = os.path.join(__RES__, __EXE__ + '.desktop')
  with open(autostart_template_filename, 'r') as file:
    contents = file.read()
  return contents.replace('Exec=' + __EXE__, 'Exec=' + find_executable(__EXE__))

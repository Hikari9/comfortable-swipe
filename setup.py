from __future__ import print_function

import os
import sys
from shutil import copyfile
from setuptools import setup, find_packages
from setuptools.extension import Extension
from setuptools.command.install import install

__BIN__ = os.path.dirname(sys.executable)
_SHARE_ = os.path.join(os.path.dirname(__BIN__), 'share')
__CWD__ = os.getcwd()
__DIR__ = os.path.abspath(os.path.dirname(__file__))
__URL__ = 'https://github.com/Hikari9/comfortable-swipe-ubuntu'

NAME = 'comfortable-swipe'
PYTHON_NAME = NAME.replace('-', '_')
VERSION = '1.1.0-beta'
PROGRAM = os.path.join(__BIN__, NAME)
CONFIG = os.path.join(
    _SHARE_
    if os.path.dirname(os.path.basename(_SHARE_)) == 'local'
    else os.path.join(
        os.path.dirname(os.path.dirname(_SHARE_)),
        'local',
        'share'
    ), NAME + '.conf'
)

# prioritize the higher indices
conf_paths = [
    os.path.join(__DIR__, 'defaults.conf'),
    os.path.join(os.getenv('HOME'), '.config', 'comfortable-swipe', 'comfortable-swipe.conf'),
    os.path.join('usr', 'local', 'share', 'comfortable-swipe', 'comfortable-swipe.conf'),
    CONFIG
]

# for C++ library
cpp_macros = dict(
    __COMFORTABLE_SWIPE__PROGRAM__='"{}"'.format(PROGRAM),
    __COMFORTABLE_SWIPE__VERSION__='"{}"'.format(VERSION),
    __COMFORTABLE_SWIPE__CONFIG__='"{}"'.format(CONFIG)
)

try:
    # make sure working directory is here
    os.chdir(__DIR__)

    # save README as long_description
    with open('README.md', 'r') as README_file:
        README = README_file.read()

    # save LICENSE as license
    with open('LICENSE', 'r') as LICENSE_file:
        LICENSE = LICENSE_file.read()

    # read C++ libraries for comfortable swipe
    extension_names = ['service', 'util']
    extensions = [Extension(
        name='{}.{}'.format(PYTHON_NAME, extension_name),
        define_macros=list(cpp_macros.items()),
        sources=['lib/__python__.cpp'],
        extra_compile_args=['-O2', '-Wno-unused-result'],
        libraries=['xdo']
    ) for extension_name in extension_names]

    # setup python script
    setup(
        name=NAME,
        version=VERSION,
        description='Comfortable 3-finger and 4-finger swipe gestures',
        long_description=README,
        license=LICENSE,
        author='Rico Tiongson',
        author_email='thericotiongson@gmail.com',
        url=__URL__,
        zip_safe=True,
        packages=find_packages(),
        entry_points=dict(console_scripts=['{}=comfortable_swipe:main'.format(NAME)]),
        ext_modules=extensions,
        # include program to sources so it will be removed on uninstall
    )

    # create directories if they don't exist yet
    if 'install' in sys.argv:
        os.path.exists(os.path.dirname(PROGRAM)) or os.makedirs(os.path.dirname(PROGRAM))
        os.path.exists(os.path.dirname(CONFIG)) or os.makedirs(os.path.dirname(CONFIG))

        # copy any of the old config files
        conf_files = [path for path in conf_paths if os.path.exists(path) and os.path.isfile(path)]
        print('using configuration file at', conf_files[-1])

        if conf_files[-1] != CONFIG:
            # new installation or upgrading from old version, copy to new location
            copyfile(conf_files[-1], CONFIG)

            if conf_files[-1] == os.path.join(__DIR__, 'defaults.conf'):
                # new installation - copy default configuration
                print('copying configuration file to', CONFIG)

            else:
                # upgrading - delete the deprecated config file (failsafe)
                try:
                    os.remove(conf_files[-1])
                    print('moving deprecated configuration file to', CONFIG)
                except:
                    pass

        # toggle autostart
        os.chdir(os.getenv('HOME'))
        from comfortable_swipe import service
        service.autostart()
        service.autostart()

        print('\nTry running "{} start" to test'.format(NAME))


finally:
    # move working directory back to where it was before
    os.chdir(__DIR__)

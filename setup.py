import os
import sys
from setuptools import setup, find_packages
from setuptools.extension import Extension

__BIN__ = os.path.dirname(sys.executable)
_SHARE_ = os.path.join(os.path.dirname(__BIN__), 'share')
__CWD__ = os.getcwd()
__DIR__ = os.path.abspath(os.path.dirname(__file__))
__URL__ = 'https://github.com/Hikari9/comfortable-swipe-ubuntu'

NAME = 'comfortable-swipe'
PYTHON_NAME = NAME.replace('-', '_')
VERSION = '1.1.0'
PROGRAM = os.path.join(__BIN__, NAME)
CONFIG = os.path.join(_SHARE_, NAME, NAME + '.conf')

# for C++ library
cpp_macros = dict(
    __COMFORTABLE_SWIPE__PROGRAM__='"{}"'.format(PROGRAM),
    __COMFORTABLE_SWIPE__VERSION__='"{}"'.format(VERSION),
    __COMFORTABLE_SWIPE__CONFIG__='"{}"'.format(CONFIG)
)

try:
    # make sure working directory is here
    os.chdir(__DIR__)

    # make sure paths to program and config exist
    os.makedirs(os.path.dirname(PROGRAM), exist_ok=True)
    os.makedirs(os.path.dirname(CONFIG), exist_ok=True)

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
        packages=find_packages(),
        scripts=['scripts/comfortable-swipe'],
        ext_modules=extensions
    )


finally:
    # move working directory back to where it was before
    os.chdir(__DIR__)

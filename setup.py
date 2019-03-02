import os
from setuptools import setup
from setuptools.extension import Extension

__CWD__ = os.getcwd()
__DIR__ = os.path.abspath(os.path.dirname(__file__))
__URL__ = 'https://github.com/Hikari9/comfortable-swipe-ubuntu'

NAME = 'comfortable-swipe'
VERSION = '1.1.0'
PROGRAM = os.path.join('/usr/local/bin', NAME)
CONFIG = os.path.join(PROGRAM, 'comfortable-swipe.conf')

try:
    # make sure working directory is here
    os.chdir(__DIR__)

    # save README as long_description
    with open('README.md', 'r') as README_file:
        README = README_file.read()

    # save LICENSE as license
    with open('LICENSE', 'r') as LICENSE_file:
        LICENSE = LICENSE_file.read()

    # have a dictionary of macros
    macros = dict(
        __COMFORTABLE_SWIPE__PROGRAM__=f'"{PROGRAM}"',
        __COMFORTABLE_SWIPE__VERSION__=f'"{VERSION}"',
        __COMFORTABLE_SWIPE__CONFIG__=f'"{CONFIG}"'
    )

    # read C++ library for comfortable swipe
    comfortable_swipe = Extension(
        name='comfortable_swipe',
        define_macros=list(macros.items()),
        libraries=['xdo'],
        include_dirs=['/usr/local/lib'],
        sources=['comfortable-swipe.cpp'],
        extra_compile_args=['-O2', '-Wno-unused-result']

    )

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
        # import external modules (aka. C++)
        ext_modules=[comfortable_swipe],
    )

finally:
    # move working directory back to where it was before
    os.chdir(__DIR__)

import os
from setuptools import setup, find_packages
from setuptools.extension import Extension

__CWD__ = os.getcwd()
__DIR__ = os.path.abspath(os.path.dirname(__file__))
__URL__ = 'https://github.com/Hikari9/comfortable-swipe-ubuntu'

NAME = 'comfortable-swipe'
VERSION = '1.1.0'
PROGRAM = os.path.join('/usr/local/bin', NAME)
CONFIG = os.path.join(PROGRAM, 'comfortable-swipe.conf')

# for C++ library
cpp_sources = ['comfortable-swipe.cpp']
cpp_macros = dict(
    __COMFORTABLE_SWIPE__PYTHON__='',
    __COMFORTABLE_SWIPE__PYTHON_MODULE_NAME__='"{}"'.format(NAME.replace('-', '_')),
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

    # read C++ library for comfortable swipe
    comfortable_swipe = Extension(
        name=NAME.replace('-', '_'),
        define_macros=list(cpp_macros.items()),
        libraries=['xdo'],
        include_dirs=['/usr/local/lib'],
        sources=cpp_sources,
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
        packages=find_packages(),
        ext_modules=[comfortable_swipe]
    )


finally:
    # move working directory back to where it was before
    os.chdir(__DIR__)

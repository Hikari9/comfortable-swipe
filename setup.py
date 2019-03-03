from __future__ import print_function

import os
import sys
import setuptools

from shutil import copyfile
from setuptools import setup, find_packages
from setuptools.extension import Extension
from setuptools.command.develop import develop
from setuptools.command.install import install
from wheel.bdist_wheel import bdist_wheel

NAME = 'comfortable-swipe'
PYTHON_NAME = NAME.replace('-', '_')
VERSION = '1.1.0-beta'

__BIN__ = os.path.dirname(sys.executable)
__SHARE__ = os.path.join(sys.prefix, 'local', 'share')
__CWD__ = os.getcwd()
__DIR__ = os.path.abspath(os.path.dirname(__file__))
__RES__ = os.path.join(__DIR__, PYTHON_NAME, 'res')
__URL__ = 'https://github.com/Hikari9/comfortable-swipe-ubuntu'


try:
    # make sure working directory is here
    os.chdir(__DIR__)

    # assign config
    CONFIG = os.path.join(__SHARE__, NAME, NAME + '.conf')
    DEFAULT_CONFIG = os.path.join(__RES__, 'defaults.conf')

    # prioritize the higher indices
    conf_paths = [
        DEFAULT_CONFIG,
        os.path.join(os.getenv('HOME'), '.config', 'comfortable-swipe', 'comfortable-swipe.conf'),
        os.path.join('/usr/local/share', 'comfortable-swipe', 'comfortable-swipe.conf'),
        CONFIG
    ]

    # for C++ library
    cpp_macros = dict(
        __COMFORTABLE_SWIPE__VERSION__='"{}"'.format(VERSION),
        __COMFORTABLE_SWIPE__CONFIG__='"{}"'.format(CONFIG)
    )

    # save README as long_description
    with open('README.md', 'r') as README_file:
        README = README_file.read()

    # read C++ libraries for comfortable swipe
    extension_names = ['service']
    extensions = [Extension(
        name='{}.cpp.{}'.format(PYTHON_NAME, extension_name),
        define_macros=list(cpp_macros.items()),
        sources=[os.path.join('cpp', '_python.cpp')],
        extra_compile_args=['-O2', '-Wno-unused-result'],
        libraries=['xdo']
    ) for extension_name in extension_names]


    def pre_install(self):
        pass


    def post_install(self):
        # create program/config directories
        if not os.path.exists(os.path.dirname(CONFIG)):
            os.makedirs(os.path.dirname(CONFIG))

        # copy any of the old config files
        conf_files = [path for path in conf_paths if os.path.exists(path) and os.path.isfile(path)]
        print('Using configuration file at', conf_files[-1])

        if conf_files[-1] != CONFIG:
            # new installation or upgrading from old version, copy to new location
            copyfile(conf_files[-1], CONFIG)

            if conf_files[-1] == DEFAULT_CONFIG:
                # new installation - copy default configuration
                print('Copying configuration file to', CONFIG)

            else:
                # upgrading - delete the deprecated config file (failsafe)
                print('warning: depcrecated configuration file at', conf_files[-1])
                print('         you have to remove this manually')

        # toggle autostart
        os.chdir(os.getenv('HOME'))
        from comfortable_swipe import service
        service.autostart()
        service.autostart()

        print('\nInstallation successful\nTry running "{} start"'.format(NAME))


    def pre_uninstall(self):
        # remove autostart config
        from comfortable_swipe.util import autostart_path
        from comfortable_swipe.service import autostart
        if os.path.exists(autostart_path()):
            autostart()


    def post_uninstall(self):
        # provide warning for manual removal of configuration file
        if os.path.exists(CONFIG) and os.path.isfile(CONFIG):
            print('You have to manually remove {}'.format(CONFIG))
        print('Successfully uninstalled', NAME)



    # add post_install script to install method
    class Install(install):
        def run(self):
            pre_install(self)
            install.run(self)
            post_install(self)


    class Develop(develop):
        def run(self):

            if self.uninstall:
                pre_uninstall(self)
            else:
                pre_install(self)

            develop.run(self)

            if self.uninstall:
                post_uninstall(self)
            else:
                post_install(self)

    # Override command classes here
    cmdclass = dict(Install=Install, develop=Develop, bdist_wheel=bdist_wheel)

    # setup python script
    setup_script = setup(
        name=NAME,
        version=VERSION,
        description='Comfortable 3-finger and 4-finger swipe gestures',
        long_description=README,
        license='MIT',
        author='Rico Tiongson',
        author_email='thericotiongson@gmail.com',
        url=__URL__,
        zip_safe=False,
        packages=find_packages(),
        include_package_data=True,
        entry_points=dict(console_scripts=['{}=comfortable_swipe.__main__:main'.format(NAME)]),
        ext_modules=extensions,
        cmdclass=cmdclass
    )

finally:
    # move working directory back to where it was before
    os.chdir(__CWD__)

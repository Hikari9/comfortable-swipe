from __future__ import print_function

import os
import sys
import setuptools

from shutil import copyfile
from setuptools import setup, find_packages
from setuptools.extension import Extension
from setuptools.command.develop import develop
from setuptools.command.install import install
from setuptools.command.easy_install import easy_install
from wheel.bdist_wheel import bdist_wheel


VERSION = '1.1.0-beta'
__CWD__ = os.getcwd()
__DIR__ = os.path.dirname(os.path.abspath(__file__))
__URL__ = 'https://github.com/Hikari9/comfortable-swipe-ubuntu'

extension_names = ['service']



try:
    # make sure working directory is here
    os.chdir(__DIR__)


    # save README as long_description
    with open('README.md', 'r') as README_file:
        README = README_file.read()


    # match constants with source
    from comfortable_swipe.constants import *

    # include old conf paths to list from previous versions
    conf_paths = [
        DEFAULT_CONFIG,
        os.path.join(os.getenv('HOME', ''), '.config', 'comfortable-swipe', 'comfortable-swipe.conf'),
        os.path.join('/usr/local/share', 'comfortable-swipe', 'comfortable-swipe.conf'),
        CONFIG
    ]

    # for C++ library
    cpp_macros = dict(
        COMFORTABLE_SWIPE_VERSION='"{}"'.format(VERSION),
        COMFORTABLE_SWIPE_CONFIG='"{}"'.format(CONFIG)
    )

    # read C++ libraries for comfortable swipe
    extensions = [Extension(
        name='{}.cpp.{}'.format(PYTHON_NAME, extension_name),
        define_macros=list(cpp_macros.items()),
        sources=[os.path.join('cpp', '_python.cpp')],
        extra_compile_args=['-O2', '-Wno-unused-result'],
        libraries=['xdo']
    ) for extension_name in extension_names]


    class Command:
        outer_installer = None
        outer_uninstaller = None

        def pre_install(self):
            # make sure only outer install script will run post_install
            if self.__class__.outer_installer is not None: return
            self.__class__.outer_installer = self
            print('running pre_install')

        def post_install(self):
            # make sure post_install will only run when command is outer installer
            if self.__class__.outer_installer is not self: return
            print('running post_install')

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

            # enable autostart by default
            from comfortable_swipe import autostart
            autostart.set_status(autostart.ON)
            print('Autostart created at', autostart.target_path())
            print('\nInstallation successful\nTry running: {} start'.format(NAME))

        def pre_uninstall(self):
            # make sure only outer uninstall script will run post_uninstall
            if self.__class__.outer_uninstaller is not None: return
            self.__class__.outer_uninstaller = self
            print('running pre_uninstall')


        def post_uninstall(self):
            # make sure post_uninstall will only run when command is outer uninstaller
            if self.__class__.outer_uninstaller is not self: return
            print('running post_uninstall')
            from comfortable_swipe import autostart
            if autostart.get_status() is autostart.ON:
                print('Removing autostart at', autostart.target_path())
                autostart.set_status(autostart.OFF)

    # add post_install script to install method
    def wrap_command(base_cls, uninstall=False):
        class InstallCommand(Command, base_cls):
            def run(self):
                self.pre_uninstall() if uninstall and self.uninstall else self.pre_install()
                base_cls.run(self)
                self.post_uninstall() if uninstall and self.uninstall else self.post_install()

        InstallCommand.__name__ = base_cls.__name__
        return InstallCommand

    # Override command classes here
    cmdclass = dict(
        install=wrap_command(install),
        easy_install=wrap_command(easy_install),
        develop=wrap_command(develop, uninstall=True),
        bdist_wheel=wrap_command(bdist_wheel)
    )

    # classifiers
    # https://pypi.org/classifiers/
    classifiers = [
        'Development Status :: 4 - Beta'
        'Intended Audience :: End Users/Desktop',
        'Operating System :: POSIX :: Linux',
        'Operating System :: Unix',
        'Programming Language :: C++',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Environment :: Console'
    ]

    # setup python script
    setup_script = setup(
        name=NAME,
        version=VERSION,
        description=DESCRIPTION,
        long_description=README,
        license='MIT',
        author='Rico Tiongson',
        author_email='thericotiongson@gmail.com',
        url=__URL__,
        zip_safe=False,
        packages=find_packages(),
        include_package_data=True,
        entry_points=dict(console_scripts=['{}={}.__main__:main'.format(NAME, PYTHON_NAME)]),
        ext_modules=extensions,
        cmdclass=cmdclass,
        install_requires=['psutil'],
        classifiers=classifiers
    )

finally:
    # move working directory back to where it was before
    os.chdir(__CWD__)

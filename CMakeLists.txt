# Run with: cmake . && make && make install
cmake_minimum_required(VERSION 3.10.2)

project(comfortable-swipe)
set(CMAKE_PROJECT_NAME "Comfortable Swipe")
set(CMAKE_PROJECT_DESCRIPTION "Comfortable 3/4-finger swipe gestures")

# creat project properties

# set flags to use C++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O2")

# set main directories
set(comfortable_swipe_bin "${CMAKE_INSTALL_PREFIX}/bin")
set(comfortable_swipe_lib "${CMAKE_INSTALL_PREFIX}/lib")
set(comfortable_swipe_share "${CMAKE_INSTALL_PREFIX}/share")
set(comfortable_swipe_include "${CMAKE_INSTALL_PREFIX}/include")

# set version from VERSION file
file(STRINGS "VERSION" comfortable_swipe_version)

# set project variables
set(comfortable_swipe_exe_path "${comfortable_swipe_bin}/comfortable-swipe")
set(comfortable_swipe_conf_path "/usr/local/share/comfortable-swipe/comfortable-swipe.conf")

# C++ definitions
add_definitions(
  -DCOMFORTABLE_SWIPE_VERSION="${comfortable_swipe_version}"
  -DCOMFORTABLE_SWIPE_PROGRAM="${comfortable_swipe_exe_path}"
  -DCOMFORTABLE_SWIPE_CONFIG="${comfortable_swipe_conf_path}"
)

# add our build-time only static library
add_library(comfortable-swipe.lib STATIC "src/comfortable_swipe.cpp")
target_include_directories(comfortable-swipe.lib PUBLIC "src")

# register comfortable-swipe command line program
add_executable("comfortable-swipe" "comfortable-swipe.cpp")

# link libraries here
find_library(XDO libxdo.so)
target_link_libraries(comfortable-swipe.lib "${XDO}")
target_link_libraries(comfortable-swipe comfortable-swipe.lib)

# perform installation
install(TARGETS comfortable-swipe DESTINATION bin)

# set platform-specific tasks
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Rico Tiongson <thericotiongson@gmail.com>") #required
include(CPack)

# HEADER: versions
cmake_minimum_required(VERSION 3.10.2)
project(comfortable-swipe)

# link external C++ libraries here
find_library(XDO_LIB libxdo.a)

# CMAKE variables
set(CMAKE_INSTALL_PREFIX "/home/rico/Git/comfortable-swipe-ubuntu/dist")
set(CMAKE_PROJECT_NAME "comfortable-swipe")
set(CMAKE_PROJECT_DESCRIPTION "3/4-finger comfortableswipe gestures")
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# set flags to use C++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O2")

# set main directories
set(comfortable_swipe_bin "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(comfortable_swipe_lib "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(comfortable_swipe_share "${CMAKE_CURRENT_BINARY_DIR}/share")
set(comfortable_swipe_include "${CMAKE_CURRENT_BINARY_DIR}/include")

# set version from VERSION file
file(STRINGS "VERSION" comfortable_swipe_version)

# set project variables
set(comfortable_swipe_exe_source "${CMAKE_CURRENT_SOURCE_DIR}/comfortable-swipe.cpp")
set(comfortable_swipe_exe_path "${comfortable_swipe_bin}/comfortable-swipe")
set(comfortable_swipe_conf_path "/usr/local/share/comfortable-swipe/comfortable-swipe.conf")

# C++ definitions
add_definitions(
  -DCMAKE_BUILD 1
  -DCOMFORTABLE_SWIPE_VERSION="${comfortable_swipe_version}"
  -DCOMFORTABLE_SWIPE_PROGRAM="${comfortable_swipe_exe_path}"
  -DCOMFORTABLE_SWIPE_CONFIG="${comfortable_swipe_conf_path}"
)

# add our own comfortable-swipe library
add_library(comfortable-swipe.a STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/comfortable_swipe.cpp")
target_include_directories(comfortable-swipe.a PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set_target_properties(comfortable-swipe.a PROPERTIES OUTPUT_NAME "comfortable-swipe")

# register comfortable-swipe command line program
add_executable("comfortable-swipe" "${comfortable_swipe_exe_source}")

# add libraries to target
target_link_libraries(comfortable-swipe.a "${XDO_LIB}")
target_link_libraries(comfortable-swipe comfortable-swipe.a)

# perform installation
install(TARGETS comfortable-swipe DESTINATION bin)

# set platform-specific tasks
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Rico Tiongson <thericotiongson@gmail.com>") #required
include(CPack)

CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)
# find external libraries here
FIND_LIBRARY(XDO_LIB libxdo)

# set comfortable swipe version
FILE(STRINGS "VERSION" VERSION)
ADD_DEFINITIONS(-DCOMFORTABLE_SWIPE_VERSION="${VERSION}")

# set project
PROJECT (comfortable-swipe)

# add our own library
ADD_LIBRARY(comfortableswipe STATIC comfortable_swipe/lib.cpp)

# set our target library output
#SET_TARGET_PROPERTIES(comfortableswipe
#  PROPERTIES
#  LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/library
#)

# set our library includes
TARGET_INCLUDE_DIRECTORIES(comfortableswipe
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/comfortable_swipe"
)

# add comfortable-swipe command line program
ADD_EXECUTABLE(comfortable-swipe command_line.cpp)

# link target libraries for program
TARGET_LINK_LIBRARIES(comfortable-swipe comfortableswipe)
TARGET_LINK_LIBRARIES(comfortable-swipe "${XDO_LIB}")

INSTALL(TARGETS comfortable-swipe
    COMPONENT linapp
    RUNTIME DESTINATION "/home/rico/cf/run"
    LIBRARY DESTINATION "/home/rico/cf/run"
    DESTINATION "/home/rico/cf/run"
)


SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "KK") #required
INCLUDE(CPack)

project(Babel)

cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g3")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)


# C VERSION OF THE CODE (WORKING)
# set(SOURCES_CLIENT
# #   ./client/v1/main.cpp
# #   ./client/v1/blockingclient.cpp
# #   ./client/v1/fortunethread.cpp
# #   ./client/v1/blockingclient.hpp
# #   ./client/v1/fortunethread.hpp
# #   ./client/v2/main.cpp
# #   ./client/v2/client.cpp
# #   ./client/v2/client.hpp
# #    ./client/v3/main.cpp
# #    ./client/v3/help.hpp
#    ./client/main.cpp
#    ./client/myudp.cpp
#    ./client/mythread.cpp
#     )

# C++ VERSION OF THE CODE (NOT WORKING YET)
file(GLOB_RECURSE CLIENT_SRCS "./Srcs/Client/*.cpp")


include_directories(${CMAKE_INCLUDE_PATH})
add_executable(babel_client WIN32 ${CLIENT_SRCS})
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui -lpthread -lportaudio)


# C VERSION OF THE CODE (WORKING)
# set(SOURCES_SERVER
#   server/main.cpp
#   )

# C++ VERSION OF THE CODE (NOT WORKING YET)
file(GLOB_RECURSE SERVER_SRCS "./Srcs/Server/*.cpp")


add_executable(babel_server WIN32 ${SERVER_SRCS})
target_link_libraries(babel_server ${CONAN_LIBS})

add_custom_command(TARGET babel_server POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                      $<TARGET_FILE:babel_server> $(CMAKE_SOURCE_DIR))

add_custom_command(TARGET babel_client POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                      $<TARGET_FILE:babel_client> $(CMAKE_SOURCE_DIR))
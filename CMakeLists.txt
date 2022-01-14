# Your CMakeLists.txt for the main App project
# This time what is new is I have added:
# 1.) another 'add_executable'
# 2.) another 'target_link_libraries'
#
# Observe now you will have two projects setup.
# As they stand, they will be identical.
####################################################
# The minimum required version of CMake to ouse
cmake_minimum_required(VERSION 3.10)


# Set the project name to your project name
project(
    App             # Name of our application
    VERSION 1.0     # Version of our software
    LANGUAGES CXX)  # Language that we are using
# We can additionally set the langauge standard for
# C++
set(CMAKE_CXX_STANDARD 17)


# Where are the include directories
include_directories("/usr/local/Cellar/sfml/2.5.1_1/include")
include_directories("./include/")

# Where are the libraries
# Hint: On linux you can grep for them: ldconfig -p | grep sfml
link_directories("/usr/local/Cellar/sfml/2.5.1_1/lib")


# Add the source code files to a specific project
# We can indeed have multiple executables generated from
# one CMakeLists.txt file.
# For example, we might have test files that we want
# to generate.
add_executable(App ./src/App.cpp ./src/Command.cpp ./src/Draw.cpp ./src/UDPNetworkServer.cpp ./src/UDPNetworkClient.cpp ./src/main.cpp)

add_executable(App_Test ./src/App.cpp ./src/Command.cpp ./src/Draw.cpp ./src/UDPNetworkServer.cpp ./src/UDPNetworkClient.cpp ./tests/main_test.cpp)

# Add any libraries
# On linux, you can use the handy 'apt-file' tool to find
# where exactly header files exist. See example below:
# 	sudo apt install apt-file
#   	sudo apt-file update
# 	apt-file find Texture.hpp

find_package(OpenGL REQUIRED)
# Print out the path for debugging purposes
message(STATUS "Found OpenGL at path: ${OPENGL_INCLUDE_DIR}")
include_directories(${OPENGL_INCLUDE_DIR})

target_link_libraries(App sfml-graphics sfml-window sfml-system sfml-network ${OPENGL_LIBRARY})
target_link_libraries(App_Test sfml-graphics sfml-window sfml-system sfml-network ${OPENGL_LIBRARY})

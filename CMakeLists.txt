cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)  

project ("Template")

#include(FetchContent)
#
#set(GLFW_SOURCE_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW)
#FetchContent_Declare(
#  GLFW
#  GIT_REPOSITORY https://github.com/glfw/glfw.git
#  GIT_TAG 3.3.8
#  SOURCE_DIR ${GLFW_SOURCE_DIR}
#)
#
#FetchContent_MakeAvailable(GLFW)

find_package(OpenGL REQUIRED)

add_subdirectory(Source/Mathematics)
add_subdirectory(Source/Mathematics/LinearAlgebra)
add_subdirectory(Tests/GLFWTest) 
add_subdirectory(Tests/UniversalTest) 




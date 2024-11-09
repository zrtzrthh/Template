cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)  

project ("Template" LANGUAGES CXX CUDA)

find_package(OpenGL REQUIRED)

add_subdirectory(Source/Mathematics)
add_subdirectory(Source/Mathematics/LinearAlgebra)
add_subdirectory(Tests/GLFWTest) 
add_subdirectory(Tests/UniversalTest) 




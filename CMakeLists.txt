cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)  

project ("Template" LANGUAGES CXX CUDA)

find_package(OpenGL REQUIRED)

add_subdirectory(Source/Mathematics)
add_subdirectory(Cuda/CudaTest)
add_subdirectory(Tests/GLFWTest) 




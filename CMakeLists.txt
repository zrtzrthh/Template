cmake_minimum_required (VERSION 3.8)

project ("Template" LANGUAGES CXX CUDA)

find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})

add_subdirectory(Tests) 
add_subdirectory(Source/Mathematics)
add_subdirectory(Cuda/CudaTest) 




file(GLOB_RECURSE MATH_LIB_SRC          *.cpp
							                 Calculus/*.cpp)

add_library(Mathematics STATIC ${MATH_LIB_SRC})

target_include_directories(Mathematics PUBLIC .
                                              ./Calculus
                                              ./LinearAlgebra)

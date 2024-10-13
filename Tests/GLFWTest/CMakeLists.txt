add_executable(GLFWTest GLFW.cpp)

include_directories(${CMAKE_SOURCE_DIR}/ThirdPart)

link_directories(${CMAKE_SOURCE_DIR}/ThirdPart)

target_link_libraries(GLFWTest OpenGL::GL
                               ${CMAKE_SOURCE_DIR}/ThirdPart/GLFW/glfw3.lib)


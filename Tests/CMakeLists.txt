#target_include_directories(MYLIB PUBLIC ${CMAKE_SOURCE_DIR}/Sourcce/Mathematics)

add_executable(MyDiff main.cpp)

target_link_libraries(MyDiff Mathematics)

add_executable(MyDiff2 main1.cpp)

target_link_libraries(MyDiff2 Mathematics)


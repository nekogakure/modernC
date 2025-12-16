cmake_minimum_required(VERSION 4.0)
project(modernC C)

set(CMAKE_C_STANDARD 23)

add_library(modernC STATIC src/modern.c
        src/m_var.c
        include/m_var.h
        src/m_result.c
        include/m_result.h
        src/m_vec.c
        include/m_vec.h
        include/modern.h
        include/m_option.h)

add_executable(example-fizzbuzz example/fizzbuzz.c)
add_executable(example-string example/string_demo.c)
add_executable(example-vector example/vec_demo.c)
add_executable(example-panic example/panic_demo.c)
add_executable(example-result example/result_option_demo.c)

target_link_libraries(example-fizzbuzz PRIVATE modernC)
target_link_libraries(example-string PRIVATE modernC)
target_link_libraries(example-vector PRIVATE modernC)
target_link_libraries(example-panic PRIVATE modernC)
target_link_libraries(example-result PRIVATE modernC)
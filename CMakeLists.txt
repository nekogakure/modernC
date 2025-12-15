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

add_executable(example example/main.c)
target_link_libraries(example PRIVATE modernC)
cmake_minimum_required(VERSION 3.20.0)

set(TASK4_ADD "task4_add")

add_executable(${TASK4_ADD} task4_add.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${TASK4_ADD} PRIVATE OpenMP::OpenMP_CXX)
endif()

set_target_properties(${TASK4_ADD} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../
)

add_compile_options(-fopenmp)
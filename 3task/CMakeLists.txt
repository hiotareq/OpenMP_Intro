cmake_minimum_required(VERSION 3.20.0)

set(TASK3_ADD "task3_add")

add_executable(${TASK3_ADD} task3_add.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${TASK3_ADD} PRIVATE OpenMP::OpenMP_CXX)
endif()

set_target_properties(${TASK3_ADD} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../
)

add_compile_options(-fopenmp)
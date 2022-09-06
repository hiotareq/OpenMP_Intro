cmake_minimum_required(VERSION 3.20.0)

set(TASK2_MAIN "task2_main")
set(TASK2_ADD "task2_add")

add_executable(${TASK2_MAIN} task2_main.cpp)
add_executable(${TASK2_ADD} task2_add.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${TASK2_MAIN} PRIVATE OpenMP::OpenMP_CXX)
    target_link_libraries(${TASK2_ADD} PRIVATE OpenMP::OpenMP_CXX)
endif()

set_target_properties(${TASK2_MAIN} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../
)
set_target_properties(${TASK2_ADD} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../
)

add_compile_options(-fopenmp)
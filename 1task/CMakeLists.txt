cmake_minimum_required(VERSION 3.20.0)

set(TASK1_MAIN "task1_main")
add_executable(${TASK1_MAIN} task1_main.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${TASK1_MAIN} PUBLIC OpenMP::OpenMP_CXX)
endif()

set_target_properties(${TASK1_MAIN} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../
)

set(TASK1_ADD "task1_add")
add_executable(${TASK1_ADD} task1_add.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${TASK1_ADD} PUBLIC OpenMP::OpenMP_CXX)
endif()

set_target_properties(${TASK1_ADD} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../
)

add_compile_options(-fopenmp)
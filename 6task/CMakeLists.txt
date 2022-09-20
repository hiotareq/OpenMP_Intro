cmake_minimum_required(VERSION 3.20.0)

set(TASK6_ADD "task6_add")

add_executable(${TASK6_ADD} task6_add.cpp)

find_package(OpenMp)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${TASK6_ADD} PRIVATE OpenMp::OpenMP_CXX)
endif()

set_target_properties(${TASK6_ADD} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../    
)

add_compile_options(-fopenmp)
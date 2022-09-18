cmake_minimum_required(VERSION 3.20.0)

set(TASK5_ADD "task5_add")

add_executable(${TASK5_ADD} task5_add.cpp)

find_package(OpenMp)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${TASK5_add} PRIVATE OpenMp::OpenMP_CXX)
endif()

set_target_properties(${TASK5_ADD} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../    
)

add_compile_options(-fopenmp)
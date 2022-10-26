cmake_minimum_required(VERSION 3.20.0)

set(TASK8_ADD "task8_add")

add_executable(${TASK8_ADD} task8_add.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${TASK8_ADD} PRIVATE OpenMP::OpenMP_CXX)
endif()

set_target_properties(${TASK8_ADD} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../    
)

add_compile_options(-fopenmp)
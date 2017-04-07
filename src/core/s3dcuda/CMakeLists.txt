cmake_minimum_required(VERSION 2.8)

project(s3dcuda)

find_package(CUDA QUIET REQUIRED)

set(CUDA_64_BIT_DEVICE_CODE ON)
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -std=c++11 -arch=sm_52" )

include_directories(include)

file(GLOB_RECURSE SRC_FILES
        src/*.cu
        src/*.cpp)

cuda_add_library(
    ${PROJECT_NAME}
    ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${CUDA_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
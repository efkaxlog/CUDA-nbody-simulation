cmake_minimum_required(VERSION 3.1)

project(OpenGL)

find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(CUDA QUIET REQUIRED)
find_package(CUDA QUIET REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 

set(CUDA_TOOLKIT_ROOT_DIR "/usr/local/cuda")

set(
    CUDA_NVCC_FLAGS
    ${CUDA_NVCC_FLAGS};
    -O3
    -gencode arch=compute_52,code=sm_52
    --ptxas-options=-v
    -use_fast_math
)


pkg_search_module(GLFW REQUIRED glfw3)

include_directories(library ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

cuda_add_executable(
    main
    nbody.cu
    main.cpp
    particle.cpp
    utils.cpp
    physics.cpp
    camera.cpp
    shader.cpp
    render.cpp
    controls.cpp
    simulation.cpp
)

target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_STATIC_LIBRARIES})

project(UnscentedKF)

cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++11)

#include_directories(/usr/include/python2.7)
#include_directories(/usr/local/lib/python2.7/dist-packages/numpy/core/include)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(sources src/ukf.cpp src/main.cpp src/tools.cpp src/measurement_package.h) #src/matplotlibcpp.h

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 
include_directories(/usr/local/opt/openssl/include)

link_directories(/usr/local/lib)
link_directories(/usr/local/opt/openssl/lib)
link_directories(/usr/local/Cellar/libuv/1.11.0/lib)
link_directories(/usr/include)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 


add_executable(UnscentedKF ${sources})

target_link_libraries(UnscentedKF z ssl uv uWS python2.7) #python2.7 ${PYTHON_LIBRARIES} numpy

cmake_minimum_required(VERSION 3.0)

project(OptimizationBenchmark VERSION 0.1.0)


if(NOT CMAKE_BUILD_TYPE OR
   NOT CMAKE_BUILD_TYPE STREQUAL "Release" OR
   NOT CMAKE_BUILD_TYPE STREQUAL "Debug"
)
   set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type: Release or Debug" FORCE)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Correctness options
add_compile_options(
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<CXX_COMPILER_ID:GNU>:-Wall>
  $<$<CXX_COMPILER_ID:GNU>:-Wextra>
  )

# Optimization options
add_compile_options(
  $<$<CXX_COMPILER_ID:MSVC>:/openmp>
  $<$<CXX_COMPILER_ID:GNU>:-fopenmp>
  -O0
  )

find_package(Threads REQUIRED)

add_executable(benchmark main.cxx)
target_link_libraries(benchmark PRIVATE
  $<$<CXX_COMPILER_ID:GNU>:gomp>
  Threads::Threads
  )

get_source_file_property(BENCHMARK_COMPILE_FLAGS main.cxx COMPILE_FLAGS)
message(STATUS "=== Build summary ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

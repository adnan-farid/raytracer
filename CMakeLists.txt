cmake_minimum_required(VERSION 3.20)
project(Raytracer LANGUAGES CXX)

# change later
add_executable(app src/main.cpp)

target_include_directories(app PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(app PRIVATE cxx_std_20) # cpp 20


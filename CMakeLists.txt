cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(universal)

add_executable(universal main.cpp)

target_include_directories(
    universal PUBLIC 
    file  
    gui  
    impl  
    ipc  
    network  
    reflection  
    terminal
)

target_link_libraries(universal)



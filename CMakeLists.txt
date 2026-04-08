cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 26)

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



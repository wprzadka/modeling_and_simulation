cmake_minimum_required(VERSION 3.13)
project(n-body-problem)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(${PROJECT_NAME}
        main.cpp
        src/Body.cpp
        src/LinearVidmo.cpp
)

target_link_libraries(${PROJECT_NAME} -lsfml-window -lsfml-graphics -lsfml-system)

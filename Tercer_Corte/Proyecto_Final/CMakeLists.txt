cmake_minimum_required(VERSION 3.10)
project(HealthSync_ALSE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Sql Charts REQUIRED)

include_directories(include)

set(SOURCES 
    src/main.cpp
    src/DatabaseManager.cpp
    src/Login.cpp
    src/Usuario.cpp
    src/Principal.cpp
    src/Calculo.cpp
    include/Calculo.h
    include/DatabaseManager.h   
    include/Login.h
    include/Usuario.h
    include/Principal.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(HealthSync_ALSE Qt5::Widgets Qt5::Sql Qt5::Charts)

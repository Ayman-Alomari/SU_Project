cmake_minimum_required(VERSION 3.5)

project(
    SU_Eksamen
    VERSION 1.0
    LANGUAGES CXX
)

find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)
if(NOT Qt5_FOUND)
    message(FATAL_ERROR "Qt5 not found! Please install Qt5.")
endif()

add_executable(SU_Eksamen main.cpp)
target_sources(SU_Eksamen PRIVATE enemy.cpp enemy.h)
target_sources(SU_Eksamen PRIVATE hero.cpp hero.h)


target_link_libraries(SU_Eksamen Qt5::Core Qt5::Quick Qt5::Sql)

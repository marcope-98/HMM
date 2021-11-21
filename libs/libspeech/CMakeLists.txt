cmake_minimum_required(VERSION 3.10.2)

set(PROJECT_NAME 
        libspeech)
set(LIBRARY_NAME 
        libspeech)
set(LIBRARY_HEADERS_DIR
        include/${LIBRARYNAME})
set(LIBRARY_HEADERS
        ${LIBRARY_HEADERS_DIR}/AudioFile.hpp
        ${LIBRARY_HEADERS_DIR}/SoundClip.hpp
        ${LIBRARY_HEADERS_DIR}/Window.hpp
        ${LIBRARY_HEADERS_DIR}/utils.hpp)
set(LIBRARY_SOURCE_DIR
        src)
set(LIBRARY_SOURCE
        ${LIBRARY_SOURCE_DIR}/AudioFile.cpp
        ${LIBRARY_SOURCE_DIR}/SoundClip.cpp
        ${LIBRARY_SOURCE_DIR}/Window.cpp
        ${LIBRARY_SOURCE_DIR}/utils.cpp)

project(${PROJECT_NAME})

add_library(${LIBRARY_NAME}
    STATIC
        ${LIBRARY_SOURCE})

target_include_directories(${LIBRARY_NAME} 
        PRIVATE 
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
                $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>)

target_include_directories(${LIBRARY_NAME} 
        PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:include>)
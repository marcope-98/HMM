cmake_minimum_required(VERSION 3.10.2)

set(LIBRARIES_DIR libs) 
set(LIBRARIES libspeech)
set(SOURCE_DIR src)
set(SOURCE ${SOURCE_DIR}/main.cpp)
set(HEADER_DIR include)
set(HEADER ${HEADER_DIR}/main.hpp)
project(hmm LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


find_package(OpenCV REQUIRED)
find_package(ROOT REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

set(CMAKE_CXX_FLAGS "-isystem ${ROOT_INCLUDE_DIRS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

foreach(LIBRARY ${LIBRARIES})
    add_subdirectory("${LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADER})
target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        ${LIBRARIES} ${OpenCV_LIBS} ${ROOT_LIBRARIES} Eigen3::Eigen
        )

enable_testing()
add_subdirectory(tests)

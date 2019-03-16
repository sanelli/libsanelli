cmake_minimum_required(VERSION 3.13)
project(libsanelli LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Manage libraries
add_subdirectory(libs)

# Manage sanelli lib
add_library(sanelli "")
add_subdirectory(include)
add_subdirectory(src)
target_include_directories(sanelli PUBLIC include)


# Manage test executable
add_executable(testme "")
target_link_libraries(testme Catch2::Catch2)
target_link_libraries(testme sanelli)

add_subdirectory(test)
target_include_directories(testme PUBLIC ${CMAKE_CURRENT_LIST_DIR})

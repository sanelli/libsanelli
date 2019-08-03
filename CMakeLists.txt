cmake_minimum_required(VERSION 3.13)
project(libsanelli LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Manage libraries
add_subdirectory(libs)

# Manage sanelli lib
add_library(sanelli "")
set_target_properties(sanelli PROPERTIES LINKER_LANGUAGE CXX)
add_subdirectory(include)
add_subdirectory(src)
target_include_directories(sanelli PUBLIC include)

# Manage test executable
add_executable(sanelli-test "")
target_link_libraries(sanelli-test Catch2::Catch2)
target_link_libraries(sanelli-test sanelli)

add_subdirectory(test)
target_include_directories(sanelli-test PUBLIC ${CMAKE_CURRENT_LIST_DIR})

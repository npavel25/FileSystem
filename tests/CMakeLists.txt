# Specifies the minimum required version for CMake compilation
cmake_minimum_required(VERSION 3.14)

#set(CMAKE_CXX_STANDARD 17)

# Name the project
project(sample1)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)

# Collect c/c + + files and assign them to the variable SRC_LIST_C
# ${CMAKE_CURRENT_SOURCE_DIR} represents the current item directory of CMakeLists.txt
file(GLOB
    SRC_LIST_C
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Specify the. h header file directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/include
)

# Specify the. dll link library file directory
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest/lib)

# Generate the c file into the executable sample1.exe
add_executable(sample1 ${SRC_LIST_C})
target_compile_features(sample1 PUBLIC cxx_std_17)
# Specify the sample1 link library libgtest.dll and libgtest_main.dll
target_link_libraries(sample1
                      libgtest
                      libgtest_main
)
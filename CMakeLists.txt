cmake_minimum_required(VERSION 3.8)
#set(CMAKE_CXX_COMPILER "/usr/bin/c++")
#set(CMAKE_CXX_COMPILER "/usr/bin/g++-7")

project(vigenere-victory)


# ============================================================
# Set the Standard version.

include(CheckCXXCompilerFlag)

check_cxx_compiler_flag("-std=c++17" COMPILER_SUPPORTS_CXX17)
check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if (COMPILER_SUPPORTS_CXX17)
    add_definitions(-std=c++17)
elseif (COMPILER_SUPPORTS_CXX14)
    add_definitions(-std=c++14)
elseif (COMPILER_SUPPORTS_CXX11)
    add_definitions(-std=c++11)
elseif (COMPILER_SUPPORTS_CXX0X)
    add_definitions(-std=c++0x)
else ()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif ()

#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -pipe")
set(CMAKE_EXE_LINKER_FLAGS "-pthread")
set(GCC_OPTIMIZATIONS "-g -O0")
set(GCC_COVERAGE "")

# -lstdc++fs - for safe keeping (--enable-libstdcxx-filesystem-ts)

# ============================================================
# Coveralls

option(COVERALLS "Generate coveralls data" OFF)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake-coveralls)

if (COVERALLS)
    MESSAGE("MAKING COVERALLS BUILD ==============================")
    include(Coveralls)
    coveralls_turn_on_coverage()

    file(GLOB COV_SOURCE_FILES include/Lib1/*.h src/App/*.cpp src/Lib1/*.h src/Lib1/*.cpp)
    #src/App/*.cpp
    set(COVERAGE_SRCS "${COV_SOURCE_FILES}" )
    # Create the coveralls target.
    coveralls_setup("${COVERAGE_SRCS}" ON)
    #set(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -coverage -fprofile-arcs -ftest-coverage")
    #set(GCC_COVERAGE_LINK_FLAGS "-coverage -lgcov")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
    set(GCC_OPTIMIZATIONS "")
    set(GCC_COVERAGE "-lgcov")
    add_definitions(-stdlib=libc++)
endif()
# ============================================================

# ============================================================
# Boost - if required. Installed at /usr/local/include

# for boost: -O2 -fno-exceptions -fno-rtti ??
#find_package(Boost REQUIRED COMPONENTS serialization)
#set(Boost_USE_MULTITHREAD ON)
#target_link_libraries(cpp-design-patterns ${Boost_LIBRARIES})


# ============================================================


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_OPTIMIZATIONS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CATCH_HEADER_PATH ${PROJECT_SOURCE_DIR}/test/catch/catch.h)

add_subdirectory(src/Lib1)
add_subdirectory(src/App)
add_subdirectory(test)

# ============================================================
# Coveralls

enable_testing()
if(COVERALLS)
    #message("BUILD_TESTING HIT")
    add_test(RTEST ${PROJECT_SOURCE_DIR}/build/VigenereTests)
endif()



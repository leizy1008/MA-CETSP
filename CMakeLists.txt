cmake_minimum_required(VERSION 3.17)
project(MA-CETSP)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

# ------------ common --------------
include_directories("include/")
include_directories("include/Genetic/")
include_directories("include/Genetic/Crossover/")
include_directories("include/LocalSearch/")
include_directories("include/Utils/")

aux_source_directory("src/" SRC)
aux_source_directory("src/Genetic" GENETIC)
aux_source_directory("src/Genetic/Crossover" CROSSOVER)
aux_source_directory("src/LocalSearch" LOCALSEARCH)
aux_source_directory("src/Utils" UTILS)
add_executable(MA-CETSP ${SRC} ${GENETIC} ${CROSSOVER} ${LOCALSEARCH} ${UTILS})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # ------------ gurobi config windows --------------
    include_directories("")     # /include of gurobi solver
    link_directories("")            # /lib of gurobi solver

    find_library(GUROBI95 NAMES gurobi95)
    if(NOT GUROBI95)
        message(FATAL_ERROR "Failed to find Gurobi lib. Try setting CMAKE_PREFIX_PATH")
    endif()

    find_library(GUROBICPP_RELEASE NAMES gurobi_c++md2019)
    if(NOT GUROBICPP_RELEASE)
        message(FATAL_ERROR "Failed to find Gurobi C++. Try setting CMAKE_PREFIX_PATH")
    endif()

    find_library(GUROBICPP_DEBUG NAMES gurobi_c++mdd2019)
    if(NOT GUROBICPP_DEBUG)
        message(FATAL_ERROR "Failed to find Gurobi C++. Try setting CMAKE_PREFIX_PATH")
    endif()

    target_link_libraries(MA-CETSP ${GUROBI95})
    target_link_libraries(MA-CETSP optimized ${GUROBICPP_RELEASE} debug ${GUROBICPP_DEBUG})

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # ------------ server config --------------
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto")
    message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
    message("CMAKE_CXX_FLAGS_RELEASE = ${CMAKE_CXX_FLAGS_RELEASE}")

    # ------------ gurobi config linux --------------
    list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
    find_package(GUROBI REQUIRED)
    set(GUROBI_CXX_LIBRARY "$ENV{GUROBI_HOME}/lib/libgurobi_c++.a")
    include_directories(${GUROBI_INCLUDE_DIRS})

    target_link_libraries(MA-CETSP ${GUROBI_CXX_LIBRARY} ${GUROBI_LIBRARY})
endif()












cmake_minimum_required(VERSION 3.0)

set(LIB_NAME utils)
project(${LIB_NAME} CXX)

add_subdirectory(ut)

set(SRCS
    src/EnumUtils.cpp
    src/Loggers.cpp
    src/StringUtils.cpp
    )

set(HEADERS
    include/Utils/EnumUtils.hpp
    include/Utils/Exceptions.hpp
    include/Utils/Loggers.hpp
    include/Utils/StringUtils.hpp
    )

add_library(${LIB_NAME} ${SRCS})
# add_library(utils::utils ALIAS ${LIB_NAME})

target_link_libraries(${LIB_NAME}
    PUBLIC
        book::enum
        entity::enum
        managers
        fmt::fmt
    )

target_include_directories(${LIB_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        src
    )
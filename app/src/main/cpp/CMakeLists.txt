cmake_minimum_required(VERSION 3.10.2)

project("ndk")


add_library(
        native-lib
        SHARED
        native-lib.cpp
)

add_library(
        security-lib
        SHARED
        security-lib.cpp
)

add_library(
        store-lib
        SHARED
        store-lib.cpp
)

find_library(
        log-lib
        log)

target_link_libraries(
        native-lib
        ${log-lib}
)

target_link_libraries(
        security-lib
        ${log-lib})

target_link_libraries(
        store-lib
        ${log-lib})
cmake_minimum_required(VERSION 3.5.1)
project(lab1-1 C)

set(SRC src/main.c src/search.h src/search.c src/utils.h src/utils.c)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)

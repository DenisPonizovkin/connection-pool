cmake_minimum_required(VERSION 3.10.0)
project(pool)

enable_testing()
# 14 strandard is for libpqxx.
# without this lib you can use 11.
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(connection_pool)
add_subdirectory(test)

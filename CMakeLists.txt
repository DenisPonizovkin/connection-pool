cmake_minimum_required(VERSION 3.10.0)
project(pool)

enable_testing()
# 14 strandard is for libpqxx.
# without this lib you can use 11.
set(CMAKE_CXX_STANDARD 14)

find_package(Catch2 REQUIRED)
find_library(MYSQL_CONN_LIB mysqlcppconn)
if (NOT MYSQL_CONN_LIB)
	message("Install mysql connector library")
endif()
find_library(PQXX_LIB REQUIRED)
if (NOT PQXX_LIB)
	message("Install pqxx library")
endif()
find_library(PQ_LIB pq)
if (NOT PQ_LIB)
	message("Install pq library")
endif()

add_subdirectory(connection_pool)
add_subdirectory(test)

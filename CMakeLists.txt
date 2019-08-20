cmake_minimum_required(VERSION 3.12.1)
project(pool)

enable_testing()
# 14 strandard is for libpqxx.
# without this lib you can use 11.
set(CMAKE_CXX_STANDARD 14)

# set(DRIVER "mysql")
# set(CONN_CFG "user=root;pswd=Asdf123!@#;host=localhost")

# add_definitions(-DDRIVER=${DRIVER})
# add_definitions(-DCONN_CFG=${CONN_CFG})

add_subdirectory(connection_pool)
add_subdirectory(test)

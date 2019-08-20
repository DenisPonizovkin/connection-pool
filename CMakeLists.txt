cmake_minimum_required(VERSION 3.12.1)
project(pool)

enable_testing()
set(CMAKE_CXX_STANDARD 11)

# set(DRIVER "mysql")
# set(CONN_CFG "user=root;pswd=Asdf123!@#;host=localhost")

# add_definitions(-DDRIVER=${DRIVER})
# add_definitions(-DCONN_CFG=${CONN_CFG})

add_subdirectory(connection_pool)
add_subdirectory(test)

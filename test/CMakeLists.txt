set(UNIT_TEST_LIST conn)

foreach(NAME IN LISTS UNIT_TEST_LIST)
  list(APPEND UNIT_TEST_SOURCE_LIST ${NAME}.test.cpp)
endforeach()

set(TARGET_NAME tests)

include_directories(connection_pool)
include_directories(${install_dir}/connection_pool)

add_executable(${TARGET_NAME}
  main.cpp
  ${UNIT_TEST_SOURCE_LIST})

target_link_libraries(${TARGET_NAME} pthread mysqlcppconn pqxx pq)
target_link_libraries(${TARGET_NAME} connection_pool_lib)

target_include_directories(${TARGET_NAME}
  PUBLIC
  "/usr/local/include/;${PROJECT_SOURCE_DIR}/connection_pool;${PROJECT_SOURCE_DIR}/utilities")

add_test(
  NAME ${TARGET_NAME}
  COMMAND ${TARGET_NAME} -o report.xml -r junit)



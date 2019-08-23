include_directories(connection_pool)

set(TARGET_NAME connection_pool_lib)

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

ADD_LIBRARY(${TARGET_NAME}
			STATIC
			dummy.cpp)

target_include_directories(${TARGET_NAME}
  PUBLIC
  "/usr/local/include/;${PROJECT_SOURCE_DIR}/connection_pool;${PROJECT_SOURCE_DIR}/utilities")

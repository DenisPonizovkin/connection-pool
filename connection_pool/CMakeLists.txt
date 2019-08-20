include_directories(connection_pool)

set(TARGET_NAME connection_pool_lib)

ADD_LIBRARY(${TARGET_NAME}
			STATIC
			connectionHandler.cpp)

target_include_directories(${TARGET_NAME}
  PUBLIC
  "/usr/local/include/;${PROJECT_SOURCE_DIR}/connection_pool;${PROJECT_SOURCE_DIR}/utilities")

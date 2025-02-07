cmake_minimum_required(VERSION 3.17)

project(SnippySQLiteDB VERSION 1.0.0)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp)

add_executable(main src/main.cpp)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(SQLiteDB SHARED src/DBTable.cpp)

target_include_directories(SQLiteDB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(SQLiteDB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SQLiteCpp/include/)

target_include_directories(SQLiteDB 
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hpp> 
  $<INSTALL_INTERFACE:include/>)

target_link_libraries(SQLiteDB PUBLIC
  SQLiteCpp
  sqlite3
)

target_link_libraries(main PUBLIC 
  SQLiteDB
)

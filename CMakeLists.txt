add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp)

add_executable(main src/main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(main 
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hpp> 
  $<INSTALL_INTERFACE:include/>)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/build)

add_library(SQLiteDB SHARED src/hpp/SQLiteDB.hpp src/DBTable.cpp)

target_include_directories(SQLiteDB 
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hpp> 
  $<INSTALL_INTERFACE:include/>)

target_link_libraries(SQLiteDB
  SQLiteCpp
  sqlite3
)

target_link_libraries(main
  SQLiteDB
)
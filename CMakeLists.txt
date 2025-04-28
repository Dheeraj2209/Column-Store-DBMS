#cmake_minimum_required(VERSION 3.30)
#project(Column_Store_DBMS)
#
#set(CMAKE_CXX_STANDARD 14)
##find_package(TinyXML2 REQUIRED)
#
##include_directories(${TinyXML2_INCLUDE_DIRS})
##target_link_libraries(Column_Store_DBMS ${TinyXML2_LIBRARIES})
#
#
##include_directories(src/cpp)
##include_directories(src/cpp/ComputationObjects)
##include_directories(src/cpp/Engines)
##include_directories(src/cpp/include)
##include_directories(src/cpp/Schema)
##
##add_executable(Column_Store_DBMS
##    src/cpp/ComputationObjects/Query.cpp
##    src/cpp/ComputationObjects/Query.h
##    src/cpp/ComputationObjects/Tuple.cpp
##    src/cpp/ComputationObjects/Tuple.h
##    src/cpp/Engines/DataDeleter.cpp
##    src/cpp/Engines/DataDeleter.h
##    src/cpp/Engines/DataLoader.cpp
##    src/cpp/Engines/DataLoader.h
##    src/cpp/Engines/DataManipulator.cpp
##    src/cpp/Engines/DataManipulator.hpp
##    src/cpp/Engines/DataStitcher.cpp
##    src/cpp/Engines/DataStitcher.h
##    src/cpp/Engines/DDLEngine.cpp
##    src/cpp/Engines/DDLEngine.h
##    src/cpp/Engines/DMLEngine.cpp
##    src/cpp/Engines/DMLEngine.h
##    src/cpp/Engines/QueryManager.cpp
##    src/cpp/Engines/QueryManager.h
##    src/cpp/Engines/ViewManager.cpp
##    src/cpp/Engines/ViewManager.h
##    src/cpp/include/external_includes.h
##    src/cpp/include/fsnamespace.h
##    src/cpp/include/stream_includes.h
##    src/cpp/include/Tbl.hpp
##    src/cpp/Schema/CAttribute.cpp
##    src/cpp/Schema/CAttribute.h
##    src/cpp/Schema/Constraint.cpp
##    src/cpp/Schema/Constraint.h
##    src/cpp/Schema/Database.cpp
##    src/cpp/Schema/Database.h
##    src/cpp/Schema/PrimaryKey.cpp
##    src/cpp/Schema/PrimaryKey.h
##    src/cpp/Schema/Relation.cpp
##    src/cpp/Schema/Relation.h
##    src/cpp/Schema/Schema_Element.cpp
##    src/cpp/Schema/Schema_Element.h
##    src/cpp/Schema/View.cpp
##    src/cpp/Schema/View.h
##    src/cpp/ColumnStoreDB.cpp
##    src/cpp/ColumnStoreDB.h
##    src/cpp/createDB.cpp
##    src/cpp/createDB.h
##    src/cpp/main.cpp)
#
## Find TinyXML2 package
#find_package(TinyXML2 REQUIRED)
#
## Add executable first
#add_executable(Column_Store_DBMS
#        src/cpp/ComputationObjects/Query.cpp
#        src/cpp/ComputationObjects/Query.h
#        src/cpp/ComputationObjects/Tuple.cpp
#        src/cpp/ComputationObjects/Tuple.h
#        src/cpp/Engines/DataDeleter.cpp
#        src/cpp/Engines/DataDeleter.h
#        src/cpp/Engines/DataLoader.cpp
#        src/cpp/Engines/DataLoader.h
#        src/cpp/Engines/DataManipulator.cpp
#        src/cpp/Engines/DataManipulator.hpp
#        src/cpp/Engines/DataStitcher.cpp
#        src/cpp/Engines/DataStitcher.h
#        src/cpp/Engines/DDLEngine.cpp
#        src/cpp/Engines/DDLEngine.h
#        src/cpp/Engines/DMLEngine.cpp
#        src/cpp/Engines/DMLEngine.h
#        src/cpp/Engines/QueryManager.cpp
#        src/cpp/Engines/QueryManager.h
#        src/cpp/Engines/ViewManager.cpp
#        src/cpp/Engines/ViewManager.h
#        src/cpp/include/external_includes.h
#        src/cpp/include/fsnamespace.h
#        src/cpp/include/stream_includes.h
#        src/cpp/include/Tbl.hpp
#        src/cpp/Schema/CAttribute.cpp
#        src/cpp/Schema/CAttribute.h
#        src/cpp/Schema/Constraint.cpp
#        src/cpp/Schema/Constraint.h
#        src/cpp/Schema/Database.cpp
#        src/cpp/Schema/Database.h
#        src/cpp/Schema/PrimaryKey.cpp
#        src/cpp/Schema/PrimaryKey.h
#        src/cpp/Schema/Relation.cpp
#        src/cpp/Schema/Relation.h
#        src/cpp/Schema/Schema_Element.cpp
#        src/cpp/Schema/Schema_Element.h
#        src/cpp/Schema/View.cpp
#        src/cpp/Schema/View.h
#        src/cpp/ColumnStoreDB.cpp
#        src/cpp/ColumnStoreDB.h
#        src/cpp/createDB.cpp
#        src/cpp/createDB.h
#        src/cpp/main.cpp
#)
#find_package(TinyXML2 REQUIRED)
##target_link_libraries(Column_Store_DBMS PRIVATE TinyXML2::TinyXML2)
#
#
## Link TinyXML2 (after defining executable)
#target_link_libraries(Column_Store_DBMS PRIVATE TinyXML2::TinyXML2)
cmake_minimum_required(VERSION 3.15)
project(Column-Store-DBMS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(TinyXML2 REQUIRED)

# Set source directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/test)

# Collect source files
file(GLOB_RECURSE SOURCES
        "${SRC_DIR}/Schema/*.cpp"
        "${SRC_DIR}/ComputationObjects/*.cpp"
        "${SRC_DIR}/CustomTypes/*.cpp"
        "${SRC_DIR}/Data_Objects/*.cpp"
        "${SRC_DIR}/Engines/*.cpp"
)

# Create libraries
add_library(columnstore_lib STATIC ${SOURCES})
target_include_directories(columnstore_lib PUBLIC
        ${SRC_DIR}
        ${TinyXML2_INCLUDE_DIRS}
)
target_link_libraries(columnstore_lib PUBLIC tinyxml2)

# Create executables for each operation
add_executable(Create ${SRC_DIR}/main.cpp)
target_link_libraries(Create PRIVATE columnstore_lib)

add_executable(Load ${SRC_DIR}/dml_main.cpp)
target_link_libraries(Load PRIVATE columnstore_lib)

# Test executables
#add_executable(CreateTest ${TEST_DIR}/create_test.cpp)
#target_link_libraries(CreateTest PRIVATE columnstore_lib)
#
#add_executable(LoadTest ${TEST_DIR}/load_test.cpp)
#target_link_libraries(LoadTest PRIVATE columnstore_lib)
#
#add_executable(InsertTest ${TEST_DIR}/insert_test.cpp)
#target_link_libraries(InsertTest PRIVATE columnstore_lib)
#
#add_executable(UpdateTest ${TEST_DIR}/update_test.cpp)
#target_link_libraries(UpdateTest PRIVATE columnstore_lib)
#
#add_executable(DeleteTest ${TEST_DIR}/delete_test.cpp)
#target_link_libraries(DeleteTest PRIVATE columnstore_lib)
#
#add_executable(QueryTest ${TEST_DIR}/query_test.cpp)
#target_link_libraries(QueryTest PRIVATE columnstore_lib)
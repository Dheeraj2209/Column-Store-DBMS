cmake_minimum_required(VERSION 3.15)
project(ColumnStoreDBMS)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include and link directories for Homebrew
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

# Find TinyXML2
find_library(TINYXML2_LIB tinyxml2 HINTS /opt/homebrew/lib)
if(NOT TINYXML2_LIB)
    message(FATAL_ERROR "tinyxml2 library not found in /opt/homebrew/lib")
endif()

# Base source path
set(SRC_ROOT "${CMAKE_SOURCE_DIR}/src/cpp")

# Source groups
file(GLOB ENGINE_SOURCES      "${SRC_ROOT}/Engines/*.cpp")
file(GLOB SCHEMA_SOURCES      "${SRC_ROOT}/Schema/*.cpp")
file(GLOB DATAOBJECTS_SOURCES "${SRC_ROOT}/Data_Objects/*.cpp")
file(GLOB COMPUTATION_SOURCES "${SRC_ROOT}/ComputationObjects/*.cpp")
file(GLOB CUSTOMTYPES_SOURCES  "${SRC_ROOT}/CustomTypes/*.cpp")

# -----------------------
# myapp (link precompiled objects)
# -----------------------
add_executable(myapp
        ${ENGINE_SOURCES}
        ${SCHEMA_SOURCES}
        ${COMPUTATION_SOURCES}
        ${CUSTOMTYPES_SOURCES}
        ${DATAOBJECTS_SOURCES}
)
target_link_libraries(myapp PRIVATE ${TINYXML2_LIB})

# -----------------------
# createDBOOPS
# -----------------------
add_executable(createDBOOPS
        ${ENGINE_SOURCES}
        ${SCHEMA_SOURCES}
        ${DATAOBJECTS_SOURCES}
        ${COMPUTATION_SOURCES}
        ${CUSTOMTYPES_SOURCES}
        ${SRC_ROOT}/main.cpp
)
target_link_libraries(createDBOOPS PRIVATE ${TINYXML2_LIB})

# -----------------------
# loadDB
# -----------------------
add_executable(loadDB
        ${ENGINE_SOURCES}
        ${SCHEMA_SOURCES}
        ${DATAOBJECTS_SOURCES}
        ${COMPUTATION_SOURCES}
        ${CUSTOMTYPES_SOURCES}
        ${SRC_ROOT}/dml_main.cpp
)
target_link_libraries(loadDB PRIVATE ${TINYXML2_LIB})

# -----------------------
# deleteRow
# -----------------------
add_executable(deleteRow
        ${ENGINE_SOURCES}
        ${SCHEMA_SOURCES}
        ${COMPUTATION_SOURCES}
        ${DATAOBJECTS_SOURCES}
        ${CUSTOMTYPES_SOURCES}
        ${SRC_ROOT}/delete_main.cpp
)
target_link_libraries(deleteRow PRIVATE ${TINYXML2_LIB})

# -----------------------
# printTable
# -----------------------
add_executable(printTable
        ${ENGINE_SOURCES}
        ${SCHEMA_SOURCES}
        ${DATAOBJECTS_SOURCES}
        ${COMPUTATION_SOURCES}
        ${CUSTOMTYPES_SOURCES}
        ${SRC_ROOT}/print_main.cpp
)
target_link_libraries(printTable PRIVATE ${TINYXML2_LIB})

# -----------------------
# updateRow
# -----------------------
add_executable(updateRow
        ${ENGINE_SOURCES}
        ${SCHEMA_SOURCES}
        ${DATAOBJECTS_SOURCES}
        ${COMPUTATION_SOURCES}
        ${CUSTOMTYPES_SOURCES}
        ${SRC_ROOT}/update_main.cpp
)
target_link_libraries(updateRow PRIVATE ${TINYXML2_LIB})

# -----------------------
# insertRow
# -----------------------
add_executable(insertRow
        ${ENGINE_SOURCES}
        ${SCHEMA_SOURCES}
        ${DATAOBJECTS_SOURCES}
        ${COMPUTATION_SOURCES}
        ${CUSTOMTYPES_SOURCES}
        ${SRC_ROOT}/insert_main.cpp
)
target_link_libraries(insertRow PRIVATE ${TINYXML2_LIB})

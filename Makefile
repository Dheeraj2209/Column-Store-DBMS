### Compiler settings
##CXX = g++
##CXXFLAGS = -std=c++17 -Wall -I/usr/include/tinyxml2
##LDFLAGS = -ltinyxml2
##
### Directories
##SRC_DIR = src/cpp
##TEST_DIR = src/cpp/test
##BUILD_DIR = build
##
### Source files
##SOURCES = $(wildcard $(SRC_DIR)/Schema/*.cpp) \
##          $(wildcard $(SRC_DIR)/ComputationObjects/*.cpp) \
##          $(wildcard $(SRC_DIR)/CustomTypes/*.cpp) \
##          $(wildcard $(SRC_DIR)/Data_Objects/*.cpp) \
##          $(wildcard $(SRC_DIR)/Engines/*.cpp)
##
##OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)
##
### Targets
##all: create load insert update delete query tests
##
##create: $(BUILD_DIR)/Create
##load: $(BUILD_DIR)/Load
##insert: $(BUILD_DIR)/Insert
##update: $(BUILD_DIR)/Update
##delete: $(BUILD_DIR)/Delete
##query: $(BUILD_DIR)/Query
##
##tests: createtest loadtest inserttest updatetest deletetest querytest
##
### Main executables
##$(BUILD_DIR)/Create: $(OBJECTS) $(BUILD_DIR)/$(SRC_DIR)/main.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Load: $(OBJECTS) $(BUILD_DIR)/$(SRC_DIR)/dml_main.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Insert: $(OBJECTS) $(BUILD_DIR)/$(SRC_DIR)/insert_main.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Update: $(OBJECTS) $(BUILD_DIR)/$(SRC_DIR)/update_main.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Delete: $(OBJECTS) $(BUILD_DIR)/$(SRC_DIR)/delete_main.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Query: $(OBJECTS) $(BUILD_DIR)/$(SRC_DIR)/query_main.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
### Test executables
##$(BUILD_DIR)/CreateTest: $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/create_test.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/LoadTest: $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/load_test.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/InsertTest: $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/insert_test.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/UpdateTest: $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/update_test.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/DeleteTest: $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/delete_test.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/QueryTest: $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/query_test.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
### Object files
##$(BUILD_DIR)/%.o: %.cpp
##	mkdir -p $(@D)
##	$(CXX) $(CXXFLAGS) -c $< -o $@
##
### Clean
##clean:
##	rm -rf $(BUILD_DIR)
##
##.PHONY: all clean create load insert update delete query tests createtest loadtest inserttest updatetest deletetest querytest
#
## Compiler settings
##CXX = g++
##CXXFLAGS = -std=c++17 -Wall -I/usr/include/tinyxml2 -I/opt/homebrew/include
##LDFLAGS = -L/opt/homebrew/lib -ltinyxml2 -std=c++17
##
### Directories
##SRC_DIR = src/cpp
##TEST_DIR = src/cpp/test
##BUILD_DIR = build
##
### Source files
##SOURCES = $(wildcard $(SRC_DIR)/Schema/*.cpp) \
##          $(wildcard $(SRC_DIR)/ComputationObjects/*.cpp) \
##          $(wildcard $(SRC_DIR)/CustomTypes/*.cpp) \
##          $(wildcard $(SRC_DIR)/Data_Objects/*.cpp) \
##          $(wildcard $(SRC_DIR)/Engines/*.cpp)
##
##OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
##
### Targets
##all: create load insert update delete query tests
##
##create: $(BUILD_DIR)/Create
##load: $(BUILD_DIR)/Load
##insert: $(BUILD_DIR)/Insert
##update: $(BUILD_DIR)/Update
##delete: $(BUILD_DIR)/Delete
##query: $(BUILD_DIR)/Query
##
##tests: createtest loadtest inserttest updatetest deletetest querytest
##
### Main executables
##$(BUILD_DIR)/Create: $(OBJECTS) $(BUILD_DIR)/$(SRC_DIR)/main.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Load: $(OBJECTS) $(BUILD_DIR)/$(SRC_DIR)/dml_main.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Insert: $(OBJECTS) $(BUILD_DIR)/$(SRC_DIR)/insert_main.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Update: $(OBJECTS) $(BUILD_DIR)/$(SRC_DIR)/update_main.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Delete: $(OBJECTS) $(BUILD_DIR)/$(SRC_DIR)/delete_main.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Query: $(OBJECTS) $(BUILD_DIR)/$(SRC_DIR)/query_main.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
### Test executables
##$(BUILD_DIR)/CreateTest: $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/create_test.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/LoadTest: $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/load_test.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/InsertTest: $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/insert_test.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/UpdateTest: $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/update_test.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/DeleteTest: $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/delete_test.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/QueryTest: $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/query_test.o
##	mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
### Object files (handles subdirectories)
##$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
##	mkdir -p $(@D)
##	$(CXX) $(CXXFLAGS) -c $< -o $@
##
### Clean
##clean:
##	rm -rf $(BUILD_DIR)
##
##.PHONY: all clean create load insert update delete query tests createtest loadtest inserttest updatetest deletetest querytest
## Compiler settings
##CXX = g++
##CXXFLAGS = -std=c++17 -Wall -I/opt/homebrew/include -I/usr/include/tinyxml2
##LDFLAGS = -L/opt/homebrew/lib -ltinyxml2
##
### Directories
##SRC_DIR = src/cpp
##TEST_DIR = src/cpp/test
##BUILD_DIR = build
##
### Source files
##SOURCES = $(wildcard $(SRC_DIR)/Schema/*.cpp) \
##          $(wildcard $(SRC_DIR)/ComputationObjects/*.cpp) \
##          $(wildcard $(SRC_DIR)/CustomTypes/*.cpp) \
##          $(wildcard $(SRC_DIR)/Data_Objects/*.cpp) \
##          $(wildcard $(SRC_DIR)/Engines/*.cpp) \
##          $(SRC_DIR)/main.cpp \
##          $(SRC_DIR)/dml_main.cpp \
##          $(SRC_DIR)/insert_main.cpp \
##          $(SRC_DIR)/update_main.cpp \
##          $(SRC_DIR)/delete_main.cpp \
##          $(SRC_DIR)/query_main.cpp
##
### Object files (mirror source structure in build dir)
##OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
##
### Targets
##all: create load insert update delete query
##
##create: $(BUILD_DIR)/Create
##load: $(BUILD_DIR)/Load
##insert: $(BUILD_DIR)/Insert
##update: $(BUILD_DIR)/Update
##delete: $(BUILD_DIR)/Delete
##query: $(BUILD_DIR)/Query
##
### Main executables
##$(BUILD_DIR)/Create: $(OBJECTS) $(BUILD_DIR)/main.o
##	@mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Load: $(OBJECTS) $(BUILD_DIR)/dml_main.o
##	@mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Insert: $(OBJECTS) $(BUILD_DIR)/insert_main.o
##	@mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Update: $(OBJECTS) $(BUILD_DIR)/update_main.o
##	@mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Delete: $(OBJECTS) $(BUILD_DIR)/delete_main.o
##	@mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
##$(BUILD_DIR)/Query: $(OBJECTS) $(BUILD_DIR)/query_main.o
##	@mkdir -p $(@D)
##	$(CXX) $^ -o $@ $(LDFLAGS)
##
### Object file rule with directory creation
##$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
##	@mkdir -p $(@D)
##	$(CXX) $(CXXFLAGS) -c $< -o $@
##
### Clean
##clean:
##	rm -rf $(BUILD_DIR)
##
##.PHONY: all clean create load insert update delete query
#
#CXX = g++
#CXXFLAGS = -std=c++17 -Wall -I/opt/homebrew/include -I/usr/include/tinyxml2
#LDFLAGS = -L/opt/homebrew/lib -ltinyxml2
#
## Directories
#SRC_DIR = src/cpp
#BUILD_DIR = build
#
## Common source files
#COMMON_SOURCES = $(wildcard $(SRC_DIR)/Schema/*.cpp) \
#                 $(wildcard $(SRC_DIR)/ComputationObjects/*.cpp) \
#                 $(wildcard $(SRC_DIR)/CustomTypes/*.cpp) \
#                 $(wildcard $(SRC_DIR)/Data_Objects/*.cpp) \
#                 $(wildcard $(SRC_DIR)/Engines/*.cpp)
#
## Object files
#COMMON_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(COMMON_SOURCES))
#
## Targets
#all: create load insert update delete query
#
#create: $(BUILD_DIR)/Create
#load: $(BUILD_DIR)/Load
#insert: $(BUILD_DIR)/Insert
#update: $(BUILD_DIR)/Update
#delete: $(BUILD_DIR)/Delete
#query: $(BUILD_DIR)/Query
#
## Executables
#$(BUILD_DIR)/Create: $(COMMON_OBJECTS) $(BUILD_DIR)/main.o
#	@mkdir -p $(@D)
#	$(CXX) $^ -o $@ $(LDFLAGS)
#
#$(BUILD_DIR)/Load: $(COMMON_OBJECTS) $(BUILD_DIR)/dml_main.o
#	@mkdir -p $(@D)
#	$(CXX) $^ -o $@ $(LDFLAGS)
#
#$(BUILD_DIR)/Insert: $(COMMON_OBJECTS) $(BUILD_DIR)/insert_main.o
#	@mkdir -p $(@D)
#	$(CXX) $^ -o $@ $(LDFLAGS)
#
#$(BUILD_DIR)/Update: $(COMMON_OBJECTS) $(BUILD_DIR)/update_main.o
#	@mkdir -p $(@D)
#	$(CXX) $^ -o $@ $(LDFLAGS)
#
#$(BUILD_DIR)/Delete: $(COMMON_OBJECTS) $(BUILD_DIR)/delete_main.o
#	@mkdir -p $(@D)
#	$(CXX) $^ -o $@ $(LDFLAGS)
#
#$(BUILD_DIR)/Query: $(COMMON_OBJECTS) $(BUILD_DIR)/query_main.o
#	@mkdir -p $(@D)
#	$(CXX) $^ -o $@ $(LDFLAGS)
#
## How to build .o files
#$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
#	@mkdir -p $(@D)
#	$(CXX) $(CXXFLAGS) -c $< -o $@
#
## Clean
#clean:
#	rm -rf $(BUILD_DIR)
#
#.PHONY: all clean create load insert update delete query

#////////////////

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17

# Libraries
LIBS := -ltinyxml2

# Directories
SRC_DIR := src
ENGINES := $(SRC_DIR)/cpp/Engines/*.cpp
SCHEMA := $(SRC_DIR)/cpp/Schema/*.cpp
DATA_OBJECTS := $(SRC_DIR)/cpp/Data_Objects/*.cpp
COMP_OBJECTS := $(SRC_DIR)/cpp/ComputationObjects/*.cpp
CUSTOM_TYPES := $(SRC_DIR)/cpp/CustomTypes/*.cpp
CPPMAINS := $(SRC_DIR)/cpp

# Targets
all: createDBOOPS load insertRow deleteRow updateRow printTable

#createDBOOPS: $(ENGINES) $(SCHEMA) $(COMP_OBJECTS) $(CPPMAINS)/main.cpp
#	$(CXX) $(CXXFLAGS) -o createDBOOPS \
#		$(ENGINES) \
#		$(SRC_DIR)/cpp/Schema/Database.cpp \
#		$(SRC_DIR)/cpp/Schema/CAttribute.cpp \
#		$(SRC_DIR)/cpp/Schema/Relation.cpp \
#		$(SRC_DIR)/cpp/Schema/Constraint.cpp \
#		$(SRC_DIR)/cpp/Schema/View.cpp \
#		$(SRC_DIR)/cpp/Schema/PrimaryKey.cpp \
#		$(SRC_DIR)/cpp/Schema/PrimaryKeyConstraint.cpp \
#		$(SRC_DIR)/cpp/Schema/UniqueKeyConstraint.cpp \
#		$(SRC_DIR)/cpp/Schema/ForeignKeyConstraint.cpp \
#		$(SRC_DIR)/cpp/ComputationObjects/Query.cpp \
#		$(SRC_DIR)/cpp/
#		$(CPPMAINS)/main.cpp \
#		$(LIBS)

createDBOOPS: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/main.cpp
	$(CXX) $(CXXFLAGS) -o createDBOOPS \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/main.cpp \
		$(LIBS)

load: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/dml_main.cpp
	$(CXX) $(CXXFLAGS) -o load \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/dml_main.cpp \
		$(LIBS)

insertRow: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/insert_main.cpp
	$(CXX) $(CXXFLAGS) -o insertRow \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/insert_main.cpp \
		$(LIBS)

deleteRow: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/delete_main.cpp
	$(CXX) $(CXXFLAGS) -o deleteRow \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/delete_main.cpp \
		$(LIBS)

updateRow: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/update_main.cpp
	$(CXX) $(CXXFLAGS) -o updateRow \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/update_main.cpp \
		$(LIBS)

printTable: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/print_main.cpp
	$(CXX) $(CXXFLAGS) -o printTable \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/print_main.cpp \
		$(LIBS)

clean:
	rm -f createDBOOPS load insertRow deleteRow updateRow printTable

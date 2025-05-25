# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17

# Libraries
LIBS := -ltinyxml2
LDFLAGS := -I/opt/homebrew/include -L/opt/homebrew/lib

# Directories
SRC_DIR := src
ENGINES := $(SRC_DIR)/cpp/Engines/*.cpp
SCHEMA := $(SRC_DIR)/cpp/Schema/*.cpp
DATA_OBJECTS := $(SRC_DIR)/cpp/Data_Objects/*.cpp
COMP_OBJECTS := $(SRC_DIR)/cpp/ComputationObjects/*.cpp
CUSTOM_TYPES := $(SRC_DIR)/cpp/CustomTypes/*.cpp
CPPMAINS := $(SRC_DIR)/cpp

# Targets
wsl: createDBOOPS load insertRow deleteRow updateRow printTable
mac: createmac loadmac insertRowmac deleteRowmac updateRowmac printTablemac unDeleteRowmac querymac

#mac executables
createmac: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/main.cpp
	$(CXX) $(CXXFLAGS) -o createDBOOPS \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/main.cpp \
		$(LDFLAGS) $(LIBS)

loadmac: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/dml_main.cpp
	$(CXX) $(CXXFLAGS) -o load \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/dml_main.cpp \
		$(LDFLAGS) $(LIBS)

insertRowmac: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/insert_main.cpp
	$(CXX) $(CXXFLAGS) -o insertRow \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/insert_main.cpp \
		$(LDFLAGS) $(LIBS)

deleteRowmac: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/delete_main.cpp
	$(CXX) $(CXXFLAGS) -o deleteRow \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/delete_main.cpp \
		$(LDFLAGS) $(LIBS)

updateRowmac: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/update_main.cpp
	$(CXX) $(CXXFLAGS) -o updateRow \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/update_main.cpp \
		$(LDFLAGS) $(LIBS)

printTablemac: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/print_main.cpp
	$(CXX) $(CXXFLAGS) -o printTable \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/print_main.cpp \
		$(LDFLAGS) $(LIBS)

unDeleteRowmac: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/undelete_main.cpp
	$(CXX) $(CXXFLAGS) -o undeleteRow \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/undelete_main.cpp \
		$(LDFLAGS) $(LIBS)

querymac: $(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) $(CPPMAINS)/query_main.cpp
	$(CXX) $(CXXFLAGS) -o queryRow \
		$(ENGINES) $(SCHEMA) $(DATA_OBJECTS) $(COMP_OBJECTS) $(CUSTOM_TYPES) \
		$(CPPMAINS)/query_main.cpp \
		$(LDFLAGS) $(LIBS)

#wsl exectables
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

cleanwsl:
	rm -f createDBOOPS load insertRow deleteRow updateRow printTable

cleanmac:
	rm -f createmac loadmac insertRowmac deleteRowmac updateRowmac printTablemac unDeleteRowmac querymac

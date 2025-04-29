## Makefile
#
#CXX = g++
#CXXFLAGS = -std=c++17
#
## Source files
#CREATE_SRC = Engines/DDLEngine.cpp Schema/Database.cpp Schema/CAttribute.cpp \
#             Schema/Relation.cpp Schema/Constraint.cpp Schema/View.cpp \
#             Schema/PrimaryKey.cpp Schema/PrimaryKeyConstraint.cpp \
#             Schema/UniqueKeyConstraint.cpp Schema/ForeignKeyConstraint.cpp \
#             ComputationObjects/Query.cpp main.cpp
#
#LOAD_SRC = Engines/*.cpp Schema/*.cpp Data_Objects/*.cpp ComputationObjects/*.cpp \
#           CustomTypes/*.cpp dml_main.cpp
#
## Platform-specific flags
#UNAME_S := $(shell uname -s)
#
#ifeq ($(UNAME_S), Darwin)
#    # macOS
#    INCLUDES = -I/opt/homebrew/include
#    LDFLAGS = -L/opt/homebrew/lib -ltinyxml2
#else
#    # Linux / WSL
#    INCLUDES =
#    LDFLAGS =
#endif
#
#.PHONY: all clean
#
#all: createDBOOPS load
#
#createDBOOPS:
#	$(CXX) $(CXXFLAGS) -o createDBOOPS $(CREATE_SRC) $(INCLUDES) $(LDFLAGS)
#
#load:
#	$(CXX) $(CXXFLAGS) -o load $(LOAD_SRC) $(INCLUDES) $(LDFLAGS)
#
#clean:
#	rm -f createDBOOPS load



# Detect platform (mac or Linux)
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    CXXFLAGS = -std=c++17 -I/opt/homebrew/include
    LDFLAGS = -L/opt/homebrew/lib -ltinyxml2
else
    CXXFLAGS = -std=c++17
    LDFLAGS =
endif

# Common source files
COMMON_SCHEMA = Schema/Database.cpp Schema/CAttribute.cpp Schema/Relation.cpp Schema/Constraint.cpp \
                Schema/View.cpp Schema/PrimaryKey.cpp Schema/PrimaryKeyConstraint.cpp \
                Schema/UniqueKeyConstraint.cpp Schema/ForeignKeyConstraint.cpp
COMMON_ENGINES = Engines/DDLEngine.cpp Engines/*.cpp
COMMON_OBJECTS = ComputationObjects/*.cpp CustomTypes/*.cpp Data_Objects/*.cpp

# Targets
all: create load update delete query

create:
	$(CXX) $(CXXFLAGS) -o createDBOOPS Engines/DDLEngine.cpp $(COMMON_SCHEMA) ComputationObjects/Query.cpp main.cpp $(LDFLAGS)

load:
	$(CXX) $(CXXFLAGS) -o load $(COMMON_ENGINES) $(COMMON_SCHEMA) $(COMMON_OBJECTS) dml_main.cpp $(LDFLAGS)

update:
	$(CXX) $(CXXFLAGS) -o update $(COMMON_ENGINES) $(COMMON_SCHEMA) $(COMMON_OBJECTS) update_main.cpp $(LDFLAGS)

delete:
	$(CXX) $(CXXFLAGS) -o delete $(COMMON_ENGINES) $(COMMON_SCHEMA) $(COMMON_OBJECTS) delete_main.cpp $(LDFLAGS)

query:
	$(CXX) $(CXXFLAGS) -o query $(COMMON_ENGINES) $(COMMON_SCHEMA) $(COMMON_OBJECTS) query_main.cpp $(LDFLAGS)

clean:
	rm -f createDBOOPS load update delete query






















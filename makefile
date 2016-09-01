#
#-- Project configuration --#
#

BINARY = sfml-app.out

# Compiler options and flags
CXX = g++
CXXFLAGS = -Wall -Wno-switch -g
DFLAGS = -MM

# Path to source files
SRC_DIR = src
# Path to include directory
INCLUDE_DIR = include
# Path to build files
OBJ_DIR = obj

# Libraries required for linking
LIBS = -lsfml-graphics -lsfml-system -lsfml-window

#
#-- Directory structure and files --#
#

# List all .cpp files, and derive their equivalent .o and .d files
SOURCES = $(shell find $(SRC_DIR) -type f -name *.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES:.cpp=.o))
DEPS    = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES:.cpp=.d))

# Set default search directory for source files
vpath %.cpp $(SRC_DIR)

#
#-- Rules --#
#

# Produce the program
.PHONY: all
all: $(BINARY)
$(BINARY): $(OBJECTS) $(DEPS)
	$(CXX) -o $(BINARY) $(OBJECTS) $(LIBS)

# Produce all object files
.PHONY: o
o: $(OBJECTS)
$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(INCLUDE_DIR)

# Dynamically produce header dependencies
.PHONY: d
d: $(DEPS)
$(OBJ_DIR)/%.d: %.cpp
#	$(CXX) $(DFLAGS) $< -MT "$*.o $*.d" -MF $*.d -I $(INCLUDE_DIR)
	$(CXX) $(DFLAGS) $< -MT $@ -MF $@ -I $(INCLUDE_DIR)

# Include dependencies
include $(DEPS)

# Build and run the project
.PHONY: run
run: $(BINARY)
	./$(BINARY)

#
#-- Cleaning routines --#
#

# Clean build files only
.PHONY: clean
clean:
	rm $(OBJECTS) $(DEPS)


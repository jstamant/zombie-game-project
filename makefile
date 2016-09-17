#
#-- Project configuration --#
#

BINARY = sfml-app.out

# Compiler options and flags
CXX      = g++
CXXFLAGS = -Wall -Wno-switch -g

# Path to source files
SRC_DIR     = src
# Path to include directory
INCLUDE_DIR = include
# Path to build files
OBJ_DIR     = obj

# Other search directories for your specific programming setup
OPT_INCLUDES =
OPT_LIBS     =

# Libraries required for linking
LIBS = -lsfml-graphics -lsfml-system -lsfml-window

#
#-- Directory structure and files --#
#

# List all .cpp files, and derive their equivalent .o and .d files
SOURCES = $(shell find $(SRC_DIR) -type f -name *.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES:.cpp=.o))
DEPS    = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES:.cpp=.d))

# Set default search directories
vpath %.cpp $(SRC_DIR)
vpath %.h   $(INCLUDE_DIR)
vpath %.o   $(OBJ_DIR)

#
#-- Rules --#
#

# Compile the program
.PHONY: all
all: $(BINARY)
$(BINARY): $(OBJECTS)
	$(CXX) -o $(BINARY) $(OBJECTS) $(OPT_LIBS) $(LIBS)

# Compile all object files and update their dependencies
$(OBJ_DIR)/%.o: %.cpp
	@echo $<
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_DIR) $(OPT_INCLUDES)
	$(CXX) -MM $< -MT "$(OBJ_DIR)/$*.o $(OBJ_DIR)/$*.d" -MF $(OBJ_DIR)/$*.d -I$(INCLUDE_DIR)
	@echo

# Include dependencies
-include $(DEPS)

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
	-rm $(OBJECTS) $(DEPS)


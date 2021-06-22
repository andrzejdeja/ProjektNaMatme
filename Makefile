# Target project name
TARGET = NaMatme

# Compiler - just because it looks nice
CC = g++

# Add new source files below
SOURCES = \
src/main.cpp \
src/Graph.cpp \
src/GraphBuilder.cpp \
src/Node.cpp 

# Add include directories here
INCLUDES = \
-Isrc

# Every file created during compilation goes here
BUILD_DIR = build

# For futrue
# DEFS = \
# -DDEBUG_MODE

# Everything which compiler should know about
FLAGS = $(INCLUDES) -Wall -O2

all: $(TARGET).out

OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(SOURCES)))

# AstPathFinder: ${objs}
# 	g++  ${objs} -o TestMatmy.out -Wall

# main.o:
# 	g++ main.cpp -c

# Graph.o: Graph.hpp
# 	g++ Graph.cpp -c

# Node.o: Node.hpp
# 	g++ Node.cpp -c

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR) 
	$(CC) -c $(FLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(TARGET).out: $(OBJS) Makefile
	$(CC) $(OBJS) -o $@

$(BUILD_DIR):
	mkdir $@


.PHONY : clean
clean:
	rm -rf $(BUILD_DIR)
# Compiler and flags
CXX = g++
INCLUDES = -IClient/Headers -IClient/Page
CXXFLAGS = -Wall -std=c++17 $(INCLUDES)

# Source files (with subdirectories specified)
SRCS = Client/TUI/CreateUI.cpp \
       ./main.cpp      # Entry

# ./main.cpp              # (PRODUCTION)
# Client/TUI/Test/test.cpp     # (UI/UX TESTING)
# Server/Test/test.cpp         # (Server TESTING)

# Convert source files to object files with build/ prefix
OBJS = $(SRCS:%.cpp=build/%.o)

# Output binary name
TARGET = SupplySync

# Default build rule (link object files into the final binary)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile each source file to its corresponding object file
build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf build $(TARGET)

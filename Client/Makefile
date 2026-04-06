# NetImgui Base Example - Makefile
# Minimal standalone example demonstrating NetImgui client setup

CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

# Directories
SRC_DIR = src
NETIMGUI_DIR = ../Code
DEAR_IMGUI_DIR = $(NETIMGUI_DIR)/ThirdParty/DearImgui
CLIENT_DIR = $(NETIMGUI_DIR)/Client

# Source files
SRCS = $(SRC_DIR)/main.cpp \
       $(DEAR_IMGUI_DIR)/imgui.cpp \
       $(DEAR_IMGUI_DIR)/imgui_draw.cpp \
       $(DEAR_IMGUI_DIR)/imgui_tables.cpp \
       $(DEAR_IMGUI_DIR)/imgui_widgets.cpp \
       $(DEAR_IMGUI_DIR)/imgui_demo.cpp

# Headers
INCLUDES = -I$(SRC_DIR) -I$(CLIENT_DIR) -I$(DEAR_IMGUI_DIR)

# Output
OUTPUT = netimgui_example

# Default target
all: $(OUTPUT)

$(OUTPUT): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

clean:
	rm -f $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)

.PHONY: all clean run

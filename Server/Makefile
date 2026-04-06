CXX      := g++

CXXFLAGS := -std=c++17 -O2 -Wno-unused-parameter -Wno-missing-field-initializers \
            -Wno-strict-aliasing -Wno-sequence-point \
            -DHAL_API_PLATFORM_GLFW_GL3=1

LDFLAGS  := -lglfw -lGL -ldl -lpthread

ROOT     := ..
IMGUI    := $(ROOT)/Code/ThirdParty/DearImgui
SERVER   := $(ROOT)/Code/ServerApp/Source
CLIENT   := $(ROOT)/Code/Client

INCLUDES := \
    -Isrc \
    -I$(ROOT)/Code \
    -I$(CLIENT) \
    -I$(ROOT)/Code/ThirdParty \
    -I$(IMGUI) \
    -I$(IMGUI)/backends \
    -I$(SERVER) \
    -I$(SERVER)/GlfwGL3

TARGET := netimgui_server

all: $(TARGET)

$(TARGET): src/main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LDFLAGS)
	@echo "Built $(TARGET)"

clean:
	rm -f $(TARGET)

.PHONY: all clean

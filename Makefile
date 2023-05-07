# Compiler
CXX = arm-linux-gnueabihf-g++
CC = arm-linux-gnueabihf-gcc
CXXFLAGS = -Wall -Werror -O3 -std=c++17

# SSH
SSH_USERNAME = pi
SSH_IP = 192.168.0.102
SSH_TARGET_FOLDER = /home/pi/
SSH_MODES_FOLDER = /home/pi/

# rgbmatrix lib
RGB_LIB_DISTRIBUTION=lib/rpi-rgb-led-matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread -static

# lua lib
LUA_LIB_DISTRIBUTION=lib/lua
LUA_INCDIR=$(LUA_LIB_DISTRIBUTION)/lua-5.4.4/install/include
LUA_LIBDIR=$(LUA_LIB_DISTRIBUTION)/lua-5.4.4/install/lib
LUA_LIBRARY_NAME=lua
LUA_LIBRARY=$(LUA_LIBDIR)/lib$(LUA_LIBRARY_NAME).a
LDFLAGS+=-L$(LUA_LIBDIR) -l$(LUA_LIBRARY_NAME) -static

# Target
TARGET = target.out
MODES = src/modes

# main
MAIN_CPP = main.cpp
MAIN_O = main.o

# src/
SRCS_DIR = src
SRCS = $(shell find $(SRCS_DIR) -name '*.cpp')
OBJS = $(patsubst $(SRCS_DIR)/%.cpp,$(SRCS_DIR)/%.o,$(SRCS))

.PHONY: all clean

all: $(TARGET) push

push: $(TARGET)
	scp $(TARGET) $(SSH_USERNAME)@$(SSH_IP):$(SSH_TARGET_FOLDER)
	scp -r $(MODES) $(SSH_USERNAME)@$(SSH_IP):$(SSH_MODES_FOLDER)

$(TARGET): $(OBJS) main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.cpp $(SRCS_DIR)/*.h
	$(CXX) $(CXXFLAGS) -o $@ $< -c -I$(LUA_INCDIR) $(RGB_INCDIR)

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(SRCS_DIR)/*.h $(RGB_INCDIR) $(LUA_INCDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(LUA_INCDIR) $(RGB_INCDIR)

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR) CXX=$(CXX) CC=$(CC)

$(LUA_LIBRARY):
	$(MAKE) -C $(LUA_LIBDIR) local CXX=$(CXX) CC=$(CC)

clean:
	rm -f *.o $(TARGET)

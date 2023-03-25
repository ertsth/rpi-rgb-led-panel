# Compiler
CXX = arm-linux-gnueabihf-g++
CC = arm-linux-gnueabihf-gcc
CXXFLAGS = -Wall -Werror -O3 -std=c++17

# SSH
SSH_USERNAME = pi
SSH_IP = 192.168.31.109
SSH_TARGET_FOLDER = /home/pi/

# rgbmatrix lib
RGB_LIB_DISTRIBUTION=lib
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread -static

# Target
TARGET = target.out

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

$(TARGET): $(OBJS) main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.cpp $(SRCS_DIR)/*.h
	$(CXX) $(CXXFLAGS) -o $@ $< -c

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(SRCS_DIR)/*.h $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR) CXX=$(CXX) CC=$(CC)

clean:
	rm -f *.o $(TARGET)

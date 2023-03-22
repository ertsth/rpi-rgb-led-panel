CXX = arm-linux-gnueabihf-g++
CC = arm-linux-gnueabihf-gcc
CXXFLAGS = -Wall -Werror -O3 -std=c++17

SSH_USERNAME = pi
SSH_IP = 192.168.31.109
SSH_TARGET_FOLDER = /home/pi/

RGB_LIB_DISTRIBUTION=lib
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread -static

TARGET = main.out
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET) push

push: $(TARGET)
	scp $(TARGET) $(SSH_USERNAME)@$(SSH_IP):$(SSH_TARGET_FOLDER)

$(TARGET): $(OBJS) $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR) CXX=$(CXX) CC=$(CC)

clean:
	rm -f $(OBJS) $(TARGET)

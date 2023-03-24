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

$(TARGET): main.o LedMatrix.o Color.o
	$(CXX) $(CXXFLAGS) -o $@ main.o LedMatrix.o Color.o $(LDFLAGS)

main.o: main.cpp src/LedMatrix.h src/Color.h
	$(CXX) $(CXXFLAGS) -o $@ $< -c

Color.o: src/Color.cpp src/Color.h
	$(CXX) $(CXXFLAGS) -o $@ $< -c

LedMatrix.o: src/LedMatrix.cpp src/LedMatrix.h src/Color.h
	$(CXX) $(CXXFLAGS) -o $@ $< -c

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR) CXX=$(CXX) CC=$(CC)

clean:
	rm -f *.o $(TARGET)

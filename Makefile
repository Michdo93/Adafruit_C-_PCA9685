
# the compiler: define as g++ for C++
CC = g++
 
# compiler flags:
CFLAGS = -Wall -pthread
LFLAGS = -lpigpio -lrt
 
# The build target 
TARGET = libPCA9685Sample.cpp PCA9685.cpp
EXECUTABLE = testServo
 
all: $(EXECUTABLE)
 
$(EXECUTABLE): ./$(EXECUTABLE)
            $(CC) $(CFLAGS) $(TARGET) -o $(EXECUTABLE) $(LFLAGS)
 
clean:
            $(RM) $(EXECUTABLE)

# the compiler: define as g++ for C++
CC = g++
# compiler flags:
CFLAGS = -Wall -pthread
LFLAGS = -lpigpio -lrt
# The build target 
TARGETSERVO = libPCA9685Sample.cpp PCA9685.cpp
TARGETMOTOR = l298n_pca9685.cpp
EXECUTABLESERVO = testServo
EXECUTABLEMOTOR = testMotor
EXECUTABLE = $(EXECUTABLESERVO) $(EXECUTABLEMOTOR)
all: $(EXECUTABLE)
$(EXECUTABLESERVO): ./$(EXECUTABLESERVO)
            $(CC) $(CFLAGS) $(TARGET) -o $(EXECUTABLESERVO) $(LFLAGS)
$(EXECUTABLEMOTOR): ./$(EXECUTABLEMOTOR)
            $(CC) $(CFLAGS) $(TARGET) -o $(EXECUTABLEMOTOR) $(LFLAGS)
clean:
            $(RM) $(EXECUTABLE)

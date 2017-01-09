#change this to "arm-linux-gnueabi-g++" if crosscompiling
CC=g++
#and add the flags for armv6: -march=armv6zk
CFLAGS=-Wall -Werror -O3 -pedantic -Icommunicator -Isensor -Icommon -c -std=c++11
LDDFLAGS=-lrt -lpthread -pthread -lboost_system -lboost_filesystem

COMMUNICATOR_SOURCES=$(wildcard common/*.cpp communicator/*.cpp)
COMMUNICATOR_OBJECTS=$(COMMUNICATOR_SOURCES:.cpp=.o)

SENSOR_SOURCES=$(wildcard common/*.cpp sensor/*.cpp)
SENSOR_OBJECTS=$(SENSOR_SOURCES:.cpp=.o)

.phony: all clean

communicator.bin: $(COMMUNICATOR_OBJECTS) Makefile
	@$(CC) $(COMMUNICATOR_OBJECTS) -o $@ $(LDDFLAGS)

sensor.bin: $(SENSOR_OBJECTS) Makefile
	@$(CC) $(SENSOR_OBJECTS) -o $@ $(LDDFLAGS)
	
all: communicator.bin sensor.bin

.cpp.o: Makefile
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf communicator/*.o sensor/*.o common/*.o communicator.bin sensor.bin 

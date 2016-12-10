CXX=g++

CXXFLAGS_SIMULATOR=-O3 -Wall -Werror -std=gnu++11 -I. -I./Shared -I./Client -I./Shared/Bimap-master -I./Shared/websocketpp-master
CXXFLAGS_SERVER=-O3 -Wall -Werror -std=gnu++11 -I. -I./Shared -I./Server -I./Shared/Bimap-master -I./Shared/websocketpp-master

LIBS_SIMULATOR=-lrt -lpthread -lboost_system -lboost_filesystem
LIBS_SERVER=-lrt -lpthread -lboost_system -lboost_filesystem

SOURCES_SIMULATOR=./Shared/DeviceSetup.cxx ./Shared/DummySensor.cxx ./Shared/ExecCommand.cxx ./Shared/FirmwareInfo.cxx ./Shared/HostFileReader.cxx ./Shared/JSONable.cxx ./Shared/Sensor.cxx ./Shared/SensorData.cxx ./Client/boost_dependencies.cxx ./Client/client.cxx
SOURCES_SERVER=./Server/boost_dependencies.cxx ./Server/server.cxx

OUT_SIMULATOR=simulator
OUT_SERVER=dserver

all: clean simulator server

simulator:
	$(CXX) $(CXXFLAGS_SIMULATOR) $(SOURCES_SIMULATOR) $(LIBS_SIMULATOR) -o $(OUT_SIMULATOR)

server:
	$(CXX) $(CXXFLAGS_SERVER) $(SOURCES_SERVER) $(LIBS_SERVER) -o $(OUT_SERVER)

clean:
	rm -f $(OUT_SIMULATOR) $(OUT_SERVER)

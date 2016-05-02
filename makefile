all:
	g++ -std=c++11 -c src/event.cc -o bin/event.o
	g++ -std=c++11 -c src/event_manager.cc -o bin/event_manager.o
	g++ -std=c++11 -c src/link.cc -o bin/link.o
	g++ -std=c++11 -c src/node.cc -o bin/node.o
	g++ -std=c++11 -c src/host.cc -o bin/host.o
	g++ -std=c++11 -c src/router.cc -o bin/router.o
	g++ -std=c++11 -c src/packet.cc -o bin/packet.o
	g++ -std=c++11 -c src/flow.cc -o bin/flow.o
	g++ -std=c++11 -c src/network.cc -o bin/network.o
	g++ -std=c++11 -c src/main.cc -o bin/main.o 
	g++ -std=c++11 bin/*.o -o NetSim.exe -lstdc++fs


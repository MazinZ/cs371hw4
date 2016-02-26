num4: TCPEchoServer-Fork.o DieWithError.o CreateTCPServerSocket.o AcceptTCPConnection.o HandleTCPClient.o
	g++ -o num4 TCPEchoServer-Fork.o DieWithError.o CreateTCPServerSocket.o AcceptTCPConnection.o HandleTCPClient.o

TCPEchoServer-Fork.o: TCPEchoServer-Fork.cpp TCPEchoServer.h
	g++ -c TCPEchoServer-Fork.cpp

DieWithError.o: DieWithError.cpp
	g++ -c DieWithError.cpp

CreateTCPServerSocket.o: CreateTCPServerSocket.cpp
	g++ -c CreateTCPServerSocket.cpp

AcceptTCPConnection.o: AcceptTCPConnection.cpp
	g++ -c AcceptTCPConnection.cpp

HandleTCPClient.o: HandleTCPClient.cpp
	g++ -c HandleTCPClient.cpp


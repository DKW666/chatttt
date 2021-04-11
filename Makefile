CC = g++
CFLAGS = -std=c++11
Server.a: Server.o
	ar -crv Main.cc  Server.o -o chatroom_server
 
Server.o: Server.cpp Server.h Common.h
	$(CC) $(CFLAGS) -c Server.cc

clean:
	rm -f *.o chat_server


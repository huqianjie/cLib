

CC = gcc -g -Wall
CFLAGS = -lev -lssl -lcrypto -lpthread -lsqlite3

OBJ  = vpnserver.o
OBJ += commom.o
OBJ += handledb.o
OBJ += sqlitex.o
OBJ += stringx.o
OBJ += backwork.o
OBJ += datalist.o
OBJ += log-util.o
OBJ += configfile.o
OBJ += socket-util.o
OBJ += configmanager.o

vpnserver:$(OBJ)
	$(CC) -o vpnserver $(OBJ) $(CFLAGS)
	rm -rf *.o
clean:
	rm -rf *.o


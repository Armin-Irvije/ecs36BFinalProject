
# Makefile for f2022, ecs36b
# https://macappstore.org/libjson-rpc-cpp/
# https://github.com/cinemast/libjson-rpc-cpp

CC = g++ -std=c++17
CFLAGS = -I/opt/homebrew/include -g

LDFLAGS = -ljsoncpp -L/opt/homebrew/lib/ -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

INC	=	ecs36b_Common.h
INC_CL	=	ClassHierarchy.h
OBJ	=	ClassHierarchy.o

# rules.
all: 	myCar LeftMotorcycle RightMotorcycle #hw5server #hw5client

#
#
# <target> : [... tab...] <dependency>
# [... tab ....] <action>

hw5client.h:		ecs36b_hw5.json
	jsonrpcstub ecs36b_hw5.json --cpp-server=hw5Server --cpp-client=hw5Client

hw5server.h:		ecs36b_hw5.json
	jsonrpcstub ecs36b_hw5.json --cpp-server=hw5Server --cpp-client=hw5Client

hw5client.o:		hw5client.cpp hw5client.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) hw5client.cpp

myCar.o:		myCar.cpp hw5server.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) myCar.cpp

LeftMotorcycle.o:		LeftMotorcycle.cpp hw5server.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) LeftMotorcycle.cpp

RightMotorcycle.o:		RightMotorcycle.cpp hw5server.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) RightMotorcycle.cpp

hw5server.o:		hw5server.cpp hw5server.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) hw5server.cpp

ClassHierarchy.o:	ClassHierarchy.cpp ClassHierarchy.h $(INC)
	$(CC) -c $(CFLAGS) ClassHierarchy.cpp

hw5server:	hw5server.o $(OBJ)
	$(CC) -o hw5server hw5server.o $(OBJ) $(LDFLAGS)

myCar:	myCar.o $(OBJ)
	$(CC) -o myCar myCar.o $(OBJ) $(LDFLAGS)

LeftMotorcycle:	LeftMotorcycle.o $(OBJ)
	$(CC) -o LeftMotorcycle LeftMotorcycle.o $(OBJ) $(LDFLAGS)

RightMotorcycle:	RightMotorcycle.o $(OBJ)
	$(CC) -o RightMotorcycle RightMotorcycle.o $(OBJ) $(LDFLAGS)

hw5client:	hw5client.o $(OBJ)
	$(CC) -o hw5client hw5client.o $(OBJ) $(LDFLAGS)

clean:
	rm -f *.o *~ core hw5client.h hw5server.h hw5client hw5server LeftMotorcycle myCar RightMotorcycle



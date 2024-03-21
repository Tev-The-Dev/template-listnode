list: main8.o
	g++ -o list main8.o

main7.o: main8.cpp list.h listnode.h
	g++ -c main8.cpp

clean: 
	rm *.o list


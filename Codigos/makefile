CCFLAGS= -Wall
CC= g++

all: algochain
		
algochain: main.o cmdline.o sha256.o
		$(CC) $(CCFLAGS) -o algochain main.o cmdline.o sha256.o

main.o: main.cc cmdline.cc sha256.cpp Array.h block.h cmdline.h dictionary.h finders.h sha256.h tools.h user.h prototypeLista.h Lista.h
		$(CC) $(CCFLAGS) -c main.cc -o main.o 

cmdline.o: cmdline.cc cmdline.h
		$(CC) $(CCFLAGS) -c cmdline.cc -o cmdline.o 

sha256.o: sha256.cpp sha256.h
		$(CC) $(CCFLAGS) -c sha256.cpp -o sha256.o

clean:
		$(RM) *.o algochain
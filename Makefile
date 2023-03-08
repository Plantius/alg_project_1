CC = g++

CompileParms = -c -Wall -std=c++11 -O2

OBJS = standaard.o territorium.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o Territorium

standaard.o: standaard.cc standaard.h
	$(CC) $(CompileParms)  standaard.cc

territorium.o: territorium.cc standaard.h constantes.h territorium.h
	$(CC) $(CompileParms)  territorium.cc

main.o: main.cc constantes.h territorium.h
	$(CC) $(CompileParms)  main.cc


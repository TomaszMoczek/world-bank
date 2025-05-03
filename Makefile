default: prog

main.o: main.cpp
	g++ -Wall -g -c main.cpp

world_bank.o: world_bank.cpp
	g++ -Wall -g -c world_bank.cpp

prog: main.o world_bank.o
	g++ -Wall -g -o world_bank main.o world_bank.o

clean:
	rm main.o
	rm world_bank.o

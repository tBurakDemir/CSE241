all: hello

hello: main.o 
	g++ main.o ConnectFour.o -o exe

main.o: main.cpp
	g++ -c -std=c++11 main.cpp ConnectFour.cpp

clean:
	rm *.o exe

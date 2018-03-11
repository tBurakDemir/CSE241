all: hello

hello: main.o 
	g++ main.o ConnectFourAbstract.o ConnectFourDiag.o ConnectFourPlus.o ConnectFourUndo.o Cell.o -o exe

main.o: main.cpp
	g++ -c -std=c++11 main.cpp ConnectFourAbstract.cpp ConnectFourDiag.cpp ConnectFourPlus.cpp ConnectFourUndo.cpp Cell.cpp


clean:
	rm *.o exe

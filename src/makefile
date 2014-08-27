all: TIDLSAnalyzer clean

TIDLSAnalyzer: main.o DataManager.o Loader.o
	g++ main.o DataManager.o Loader.o -o TIDLSAnalyzer

main.o: main.cpp
	g++ -c main.cpp

DataManager.o: DataManager.cpp
	g++ -c DataManager.cpp

Loader.o: Loader.cpp
	g++ -c Loader.cpp

clean:
	rm -rf *.o
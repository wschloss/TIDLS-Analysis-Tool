all: TIDLSAnalyzer clean

TIDLSAnalyzer: main.o DataManager.o Loader.o Generator.o Analyzer.o
	g++ main.o DataManager.o Loader.o Generator.o Analyzer.o -o TIDLSAnalyzer

main.o: main.cpp
	g++ -c main.cpp

DataManager.o: DataManager.cpp
	g++ -c DataManager.cpp

Loader.o: Loader.cpp
	g++ -c Loader.cpp

Generator.o: Generator.cpp
	g++ -c Generator.cpp

Analyzer.o: Analyzer.cpp
	g++ -c Analyzer.cpp
clean:
	rm -rf *.o
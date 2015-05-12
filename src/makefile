all: TIDLSAnalyzer clean

TIDLSAnalyzer: main.o DataManager.o Loader.o Generator.o Analyzer.o 
	g++ main.o DataManager.o Loader.o Generator.o Analyzer.o ../Minpack/cminpack-1.3.4/*.o -o TIDLS_nix

main.o: main.cpp
	g++ -c main.cpp

DataManager.o: DataManager/DataManager.cpp
	g++ -c DataManager/DataManager.cpp

Loader.o: Loader/Loader.cpp
	g++ -c Loader/Loader.cpp

Generator.o: Generator/Generator.cpp
	g++ -c Generator/Generator.cpp

Analyzer.o: Analyzer/Analyzer.cpp
	g++ -c Analyzer/Analyzer.cpp
clean:
	rm -rf *.o
all: TIDLSAnalyzer clean

TIDLSAnalyzer: DataManager.o Loader.o Generator.o GraphingPane.o TIDLS_App.o 
	 `../wx-config --cxx` DataManager.o Loader.o Generator.o GraphingPane.o TIDLS_App.o -o TIDLS_App `../wx-config --libs`

DataManager.o: fittingSrc/DataManager.cpp
	`../wx-config --cxx --cxxflags` -c fittingSrc/DataManager.cpp

Loader.o: fittingSrc/Loader.cpp
	`../wx-config --cxx --cxxflags` -c fittingSrc/Loader.cpp

Generator.o: fittingSrc/Generator.cpp
	`../wx-config --cxx --cxxflags` -c fittingSrc/Generator.cpp

GraphingPane.o: guiSrc/GraphingPane.cpp
	`../wx-config --cxx --cxxflags` -c guiSrc/GraphingPane.cpp

TIDLS_App.o: guiSrc/TIDLS_App.cpp
	`../wx-config --cxx --cxxflags` -c guiSrc/TIDLS_App.cpp

clean:
	rm -rf *.o
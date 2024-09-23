main : main.o tinyxml2.o
	g++ build/main.o build/tinyxml2.o -o build/main -std=c++14 -fpermissive >> log.txt 2>&1
main.o: src/include/Binary.h src/include/Typefigure.h src/include/Seel.h src/main.cpp src/include/Buffer.h src/include/Reflection.h src/include/Seelxml.h src/include/ToXML.h
	g++ -c src/main.cpp  -o build/main.o -std=c++14 -fpermissive	> log.txt 2>&1
tinyxml2.o: src/thirdparty/tinyxml2.h
	g++ -c src/thirdparty/tinyxml2.cpp -o build/tinyxml2.o -std=c++14 -fpermissive >> log.txt 2>&1
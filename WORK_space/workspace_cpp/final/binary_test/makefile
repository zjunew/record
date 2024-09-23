binary: binary.o binary_fun.o base64.o
	g++ -o binary binary.o binary_fun.o base64.o

binary.o: binary.cpp binary_fun.cpp base64.cpp
	g++ -c binary.cpp binary_fun.cpp base64.cpp

clean:
	del -f *.o *.exe *.data
	del /s /q bin_data\*.* ptr_user_data\*.*
xml: xml.o tinyxml2.o xml_fun.o base64.o
	g++ -o xml xml.o tinyxml2.o xml_fun.o base64.o
xml.o: xml.cpp tinyxml2.cpp xml_fun.cpp base64.cpp
	g++ -c xml.cpp tinyxml2.cpp xml_fun.cpp base64.cpp

clean:
	del -f *.o *.exe *.xml
	del /s /q xml_generate\*.*  ptr_user_xml\*.*
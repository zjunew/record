echo "compile pdadd"
g++ ./pdadd.cpp ./book.cpp -o pdadd.exe

echo "compile pdlist"
g++ ./pdlist.cpp ./book.cpp -o pdlist.exe

echo "compile pdremove"
g++ ./pdremove.cpp ./book.cpp -o pdremove.exe

echo "compile pdshow"
g++ ./pdshow.cpp ./book.cpp -o pdshow.exe
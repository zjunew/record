echo "Insert a diary:"
./pdadd.exe <diary1.txt

echo "Insert a diary:"
./pdadd.exe <diary2.txt

echo "Insert a diary:"
./pdadd.exe <diary3.txt

echo "Remove a diary"
./pdremove.exe < remove.txt
echo

echo "show the current diaries:"
./pdlist.exe
echo

echo "show a diary"
./pdshow.exe < show.txt
echo

echo "show the current diaries:"
./pdlist.exe
echo

echo "Insert a diary:"
./pdadd.exe < diary2.txt

echo "show the current diaries:"
./pdlist.exe
echo

echo "Insert a diary:"
./pdadd.exe < change.txt

echo "show the current diaries:"
./pdlist.exe
echo
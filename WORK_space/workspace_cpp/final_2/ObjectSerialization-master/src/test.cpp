#include "Serialize.h"

#include <iostream>

#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

inline void Ser_Des();
inline void printContainer();

template <typename Type>
typename enable_if<is_arithmetic<Type>::value>::type printOne(const Type &);
void printOne(const string &);
template <typename Type1, typename Type2>
void printOne(const pair<Type1, Type2> &);
template <typename Type>
void printOne(const vector<Type> &);
template <typename Type>
void printOne(const list<Type> &);
template <typename Type>
void printOne(const set<Type> &);
template <typename Type1, typename Type2>
void printOne(const map<Type1, Type2> &);
template <typename Type>
void printOne(Type *&, size_t len = 1);
template <typename Type>
void printOne(const unique_ptr<Type> &);
template <typename Type>
void printOne(const unique_ptr<Type[]> &, size_t);
template <typename Type>
void printOne(const shared_ptr<Type> &);

struct UserDefined {
    int x1;
    double x2;
    bool x3;
    string x4;
    vector<int> x5;
    void print() {
        cout << x1 << endl << x2 << endl << x3 << endl << x4 << endl;
        printOne(x5);
    }
} UD0, UDb, UDx;

int i, ix, i0                     = 3;
pair<string, int> psi, psix, psi0 = make_pair("Good", 123);
vector<int> vi, vix, vi0          = {1, 3, 5, 7};
list<int> li, lix, li0            = {2, 4, 6, 8};
set<int> si, six, si0             = {6, 7, 33, 9, 81, 31, 54};
map<string, int> msi, msix, msi0  = {pair<string, int>("SC", 666), pair<string, int>("cx", 999)};
int *pi = new int, *pix = new int, *pi0 = &i0;
int *pai = new int[5], *paix = new int[5], *pai0 = new int[5];
unique_ptr<int> upi, upix, upi0                  = unique_ptr<int>(new int(19));
unique_ptr<int[]> upai, upaix, upai0             = unique_ptr<int[]>(new int[5]);
shared_ptr<int> spi, spix, spi0                  = shared_ptr<int>(new int(89));

pair<map<string, int>, set<int>> complicated, complicatedx, complicated0 = make_pair(msi0, si0);

int main(int argc, char const *argv[]) {

    for (auto i = 0; i < 5; i++)
        pai0[i] = upai0[i] = (i + 1) * (i + 1);

    UD0.x1 = 5;
    UD0.x2 = 9.6;
    UD0.x3 = true;
    UD0.x4 = "myString";
    UD0.x5 = vi0;

    /* Set Base64 for User-defined types: Choose one and comment the other */
    // Ser::enable_base64();
    // Des::enable_base64();
    Ser::disable_base64();
    Des::disable_base64();

    cout << "\n-------- User-defined Bianry test --------\n" << endl;
    {
        UserType_Ser_Bin test_bin("./testfile/bin_UserDefined.txt");
        test_bin.serialize(UD0.x1);
        test_bin.serialize(UD0.x2);
        test_bin.serialize(UD0.x3);
        test_bin.serialize(UD0.x4);
        test_bin.serialize(UD0.x5);
    }
    {
        UserType_Des_Bin test_bin("./testfile/bin_UserDefined.txt");
        test_bin.deserialize(UDb.x1);
        test_bin.deserialize(UDb.x2);
        test_bin.deserialize(UDb.x3);
        test_bin.deserialize(UDb.x4);
        test_bin.deserialize(UDb.x5);
    }

    UDb.print();

    cout << "\n\n-------- User-defined XML test --------\n" << endl;
    {
        UserType_Ser_Xml test_xml("./testfile/xml_UserDefined.txt");
        test_xml.serialize_xml(UD0.x1, "int");
        test_xml.serialize_xml(UD0.x2, "double");
        test_xml.serialize_xml(UD0.x3, "bool");
        test_xml.serialize_xml(UD0.x4, "string");
        test_xml.serialize_xml(UD0.x5, "vector");
    }
    {
        UserType_Des_Xml test_xml("./testfile/xml_UserDefined.txt");
        test_xml.deserialize_xml(UDx.x1, "int");
        test_xml.deserialize_xml(UDx.x2, "double");
        test_xml.deserialize_xml(UDx.x3, "bool");
        test_xml.deserialize_xml(UDx.x4, "string");
        test_xml.deserialize_xml(UDx.x5, "vector");
    }

    UDx.print();

    cout << "\n\n-------- Other types test --------" << endl;

    Ser::enable_base64();
    Des::enable_base64();
    Ser_Des();
    cout << "\n----- Enable Base64 -----" << endl;
    printContainer();

    Ser::disable_base64();
    Des::disable_base64();
    Ser_Des();
    cout << "\n\n----- Disable Base64 -----" << endl;
    printContainer();

    return 0;
}

inline void Ser_Des() {
    Ser::serialize(i0, "./testfile/bin_ari.txt");
    Des::deserialize(i, "./testfile/bin_ari.txt");
    Ser::serialize_xml(i0, "int", "./testfile/xml_ari.txt");
    Des::deserialize_xml(ix, "int", "./testfile/xml_ari.txt");

    Ser::serialize(psi0, "./testfile/bin_pair.txt");
    Des::deserialize(psi, "./testfile/bin_pair.txt");
    Ser::serialize_xml(psi0, "pair＜string，int＞", "./testfile/xml_pair.txt");
    Des::deserialize_xml(psix, "pair＜string，int＞", "./testfile/xml_pair.txt");

    Ser::serialize(vi0, "./testfile/bin_vec.txt");
    Des::deserialize(vi, "./testfile/bin_vec.txt");
    Ser::serialize_xml(vi0, "vector＜int＞", "./testfile/xml_vec.txt");
    Des::deserialize_xml(vix, "vector＜int＞", "./testfile/xml_vec.txt");

    Ser::serialize(li0, "./testfile/bin_list.txt");
    Des::deserialize(li, "./testfile/bin_list.txt");
    Ser::serialize_xml(li0, "list＜int＞", "./testfile/xml_list.txt");
    Des::deserialize_xml(lix, "list＜int＞", "./testfile/xml_list.txt");

    Ser::serialize(si0, "./testfile/bin_set.txt");
    Des::deserialize(si, "./testfile/bin_set.txt");
    Ser::serialize_xml(si0, "set＜int＞", "./testfile/xml_set.txt");
    Des::deserialize_xml(six, "set＜int＞", "./testfile/xml_set.txt");

    Ser::serialize(msi0, "./testfile/bin_map.txt");
    Des::deserialize(msi, "./testfile/bin_map.txt");
    Ser::serialize_xml(msi0, "map＜string，int＞", "./testfile/xml_map.txt");
    Des::deserialize_xml(msix, "map＜string，int＞", "./testfile/xml_map.txt");

    Ser::serialize(complicated0, "./testfile/bin_complicated.txt");
    Des::deserialize(complicated, "./testfile/bin_complicated.txt");
    Ser::serialize_xml(complicated0, "complicated_type", "./testfile/xml_complicated.txt");
    Des::deserialize_xml(complicatedx, "complicated_type", "./testfile/xml_complicated.txt");

    Ser::serialize(pi0, "./testfile/bin_ptr.txt");
    Des::deserialize(pi, "./testfile/bin_ptr.txt");
    Ser::serialize_xml(pi0, "int_ptr", "./testfile/xml_ptr.txt");
    Des::deserialize_xml(pix, "int_ptr", "./testfile/xml_ptr.txt");

    Ser::serialize(pai0, "./testfile/bin_ptra.txt", 5);
    Des::deserialize(pai, "./testfile/bin_ptra.txt");
    Ser::serialize_xml(pai0, "int__ptra", "./testfile/xml_ptra.txt", 5);
    Des::deserialize_xml(paix, "int_ptra", "./testfile/xml_ptra.txt", 5);

    Ser::serialize(upi0, "./testfile/bin_uptr.txt");
    Des::deserialize(upi, "./testfile/bin_uptr.txt");
    Ser::serialize_xml(upi0, "unique_ptr＜int＞", "./testfile/xml_uptr.txt");
    Des::deserialize_xml(upix, "unique_ptr＜int＞", "./testfile/xml_uptr.txt");

    Ser::serialize(upai0, "./testfile/bin_uptra.txt", 5);
    Des::deserialize(upai, "./testfile/bin_uptra.txt");
    Ser::serialize_xml(upai0, "unique_ptr＜int［］＞", "./testfile/xml_uptrai.txt", 5);
    Des::deserialize_xml(upaix, "unique_ptr＜int［］＞", "./testfile/xml_uptrai.txt", 5);

    Ser::serialize(spi0, "./testfile/bin_sptr.txt");
    Des::deserialize(spi, "./testfile/bin_sptr.txt");
    Ser::serialize_xml(spi0, "shared_ptr＜int＞", "./testfile/xml_sptr.txt");
    Des::deserialize_xml(spix, "shared_ptr＜int＞", "./testfile/xml_sptr.txt");
}

template <typename Type>
typename enable_if<is_arithmetic<Type>::value>::type printOne(const Type &obj) {
    cout << obj;
}

void printOne(const string &obj) {
    cout << "\"" << obj << "\"";
}

template <typename Type1, typename Type2>
void printOne(const pair<Type1, Type2> &obj) {
    cout << "(";
    printOne(obj.first);
    cout << ", ";
    printOne(obj.second);
    cout << ")";
}

template <typename Type>
void printOne(const vector<Type> &obj) {
    size_t count = obj.size();
    for (auto itor = obj.begin(); count-- > 0; itor++) {
        cout << (count == obj.size() - 1 ? "[" : "");
        printOne(*itor);
        cout << (count != 0 ? ", " : "]");
    }
}

template <typename Type>
void printOne(const list<Type> &obj) {
    size_t count = obj.size();
    for (auto itor = obj.begin(); count-- > 0; itor++) {
        cout << (count == obj.size() - 1 ? "[" : "");
        printOne(*itor);
        cout << (count != 0 ? ", " : "]");
    }
}

template <typename Type>
void printOne(const set<Type> &obj) {
    size_t count = obj.size();
    for (auto itor = obj.begin(); count-- > 0; itor++) {
        cout << (count == obj.size() - 1 ? "{" : "");
        printOne(*itor);
        cout << (count != 0 ? ", " : "}");
    }
}

template <typename Type1, typename Type2>
void printOne(const map<Type1, Type2> &obj) {
    size_t count = obj.size();
    for (auto itor = obj.begin(); count-- > 0; itor++) {
        cout << (count == obj.size() - 1 ? "{" : "");
        printOne(*itor);
        cout << (count != 0 ? ", " : "}");
    }
}

template <typename Type>
void printOne(Type *&obj, size_t len) {
    cout << "[";
    for (size_t i = 0; i < len; i++)
        cout << obj[i] << (i != len - 1 ? ", " : "]");
}

template <typename Type>
void printOne(const unique_ptr<Type> &obj) {
    cout << *obj;
}

template <typename Type>
void printOne(const unique_ptr<Type[]> &obj, size_t count) {
    size_t index = 0;
    cout << "[";
    for (; index < count; index++) {
        printOne(obj[index]);
        cout << (index != count - 1 ? ", " : "]");
    }
}

template <typename Type>
void printOne(const shared_ptr<Type> &obj) {
    cout << *obj;
}

inline void printContainer() {
    cout << "\nint" << endl;
    cout << "i0: " << i0 << "; i: " << i << "; ix: " << ix << endl;

    cout << "\npair<string, int>" << endl;
    cout << "psi0: ";
    printOne(psi0);
    cout << "; psi: ";
    printOne(psi);
    cout << "; psix: ";
    printOne(psix);
    cout << endl;

    cout << "\nvector<int>" << endl;
    cout << "vi0: ";
    printOne(vi0);
    cout << "; vi: ";
    printOne(vi);
    cout << "; vix: ";
    printOne(vix);
    cout << endl;

    cout << "\nlist<int>" << endl;
    cout << "li0: ";
    printOne(li0);
    cout << "; li: ";
    printOne(li);
    cout << "; lix: ";
    printOne(lix);
    cout << endl;

    cout << "\nset<int>" << endl;
    cout << "si0: ";
    printOne(si0);
    cout << "; si: ";
    printOne(si);
    cout << "; six: ";
    printOne(six);
    cout << endl;

    cout << "\nmap<string, int>" << endl;
    cout << "msi0: ";
    printOne(msi0);
    cout << "; msi: ";
    printOne(msi);
    cout << "; msix: ";
    printOne(msix);
    cout << endl;

    cout << "\npair<map<string, int>, set<int>>" << endl;
    cout << "complicated0: ";
    printOne(complicated0);
    cout << "; complicated: ";
    printOne(complicated);
    cout << "; complicatedx: ";
    printOne(complicatedx);
    cout << endl;

    cout << "\nint *" << endl;
    cout << "*pi0: ";
    printOne(pi0);
    cout << "; *pi: ";
    printOne(pi);
    cout << "; *pix: ";
    printOne(pix);
    cout << endl;

    cout << "\nint[]" << endl;
    cout << "pai0[]: ";
    printOne(pai0, 5);
    cout << "; pai[]: ";
    printOne(pai, 5);
    cout << "; paix[]: ";
    printOne(paix, 5);
    cout << endl;

    cout << "\nunique_ptr<int[]>" << endl;
    cout << "upai0[]: ";
    printOne(upai0, 5);
    cout << "; upai[]: ";
    printOne(upai, 5);
    cout << "; upaix[]: ";
    printOne(upaix, 5);
    cout << endl;

    cout << "\nshared_ptr<int>" << endl;
    cout << "*spi0: ";
    printOne(spi0);
    cout << "; *spi: ";
    printOne(spi);
    cout << "; *spix: ";
    printOne(spix);
    cout << endl;
}
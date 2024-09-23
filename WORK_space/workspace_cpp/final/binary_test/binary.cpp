#include "binary.hpp"

using namespace std;

//first Implement a module to support binary serialization/deserialization:



int main()
{
    //arithmetic
    int_double_bin();
    //string
    string_bin();
    pair_bin();

    vector_int_bin();
    vector_double_bin();
    vector_string_bin();

    list_int_bin();
    list_double_bin();
    list_string_bin();

    set_int_bin();
    set_double_bin();
    set_string_bin();

    map_intdouble_bin();
    map_intstr_bin();
    map_strint_bin();
    map_strstr_bin();
    
    UserDefinedType_bin();

    shared_ptr_bin();
    unique_ptr_bin();
    weak_ptr_bin();
    
    
}
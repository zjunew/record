#include "xml.hpp"

using namespace std;



int main()
{
    int_double_xml();
    string_xml();

    pair_intdouble_xml();

    vector_int_xml();
    vector_double_xml();
    vector_string_xml();

    list_int_xml();
    list_double_xml();
    list_string_xml();

    set_int_xml();
    set_double_xml();
    set_string_xml();

    map_intdouble_xml();
    map_intstr_xml();
    map_strint_xml();
    map_strstr_xml();
    
    UserDefinedType_xml();

    unique_ptr_xml();
    shared_ptr_xml();
    weak_ptr_xml();
    
    test_base64();
}
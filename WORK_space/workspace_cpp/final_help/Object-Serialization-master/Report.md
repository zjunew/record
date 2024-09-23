# <center>Object-Serialization</center>

2022-ZJU-OOP Final-Project cx 

Simply run the shell script `./run.sh` to compile and run the program, which depends to the `Makefile` coded by me earlier.

## 1 Project requirements
***

### Description

In computer science, serialization is the process of translating object state into a format that can be stored/transmitted and reconstructed later.

Binary serialization uses binary encoding to produce a compact result for uses such as storage or socket-based network streams. This mechanism is especially useful if you have to handle big data where the loading/saving time is crucial.
For cases where you want to read/edit the serialized data, e.g., for software configuration, a serialization to text files (XML, JSON, etc.) is a natural choice.

Please refer to [Serialization](https://en.wikipedia.org/wiki/Serialization) for more details.

### Requirements
- Implement a module to support binary serialization/deserialization:
```cpp
int n0 = 256, n1;
// serialize object n0 to a binary file n.data
serialize(n0, "n.data");
// reconstruct object n1 from the content of n.data
deserialize(n1, "n.data");
// now n0 == n1 should be true.
```
- Implement a wrapper module of [tinyxml2](https://github.com/leethomason/tinyxml2) to support **XML** serialization:
```cpp
std::pair<int, double> pair0 = {2, 3.1}, pair1;
// serialize object pair0 to an XML file pair.xml with the name std_pair
serialize_xml(pair0, "std_pair", "pair.xml");
// reconstruct object pair1 from the content of pair.xml
deserialize_xml(pair1, "std_pair", "pair.xml");
// now pair0 == pair1 should be true.
```
The pair.xml would be something like:
```xml
<serialization>
<std_pair>
    <first val="2"/>
    <second val="3.1000000000000001"/>
</std_pair>
</serialization>
```
- Every module has its namespace.
- Both modules should at least support the serialization of arithmetic types (see `std::is_arithmetic`), C++ string type (`std::string`), and STL containers (`std::pair`, `std::vector`, `std::list`, `std::set`, and `std::map`).
- Both modules should provide a convenient mechanism (by macro, template, etc.) to support the serialization of user-defined types, e.g.,

- During testing, you should cover all the required types and options.
- **Bonus** Use binary-to-text encoding/decoding ([base64](https://en.wikipedia.org/wiki/Base64)) to implement a binary mode of XML serialization.
- **Bonus** Support the serialization of smart pointers, e.g., `std::unique_ptr`.


***

## 2 Project description

### 2.1 How to run the program
Simply run the shell script `./run.sh` to compile and run the program, which depends to the `Makefile` coded by me earlier.

### 2.2 Tested cases

It should support any combination and any nested situation of the following types in theory, but due to the complexity of test, only several representative cases are tested.

#### 2.2.1 Basic data types
The project tested many cases where all the mentioned data types are combined:

```cpp
    /**
     * @brief std::is_arithmetic contains:
     *          bool:        true   0
     *          int:         true   1
     *          int const:   true   2
     *          float:       true   3
     *          float const: true   
     *          char:        true
     *          char const:  true
     *          std::string
     * 
     *        STL containers :
     *          std::pair
     *          std::vector
     *          std::list
     *          std::set
     *          std::map
     */

    bool test_bool = true;
    char test_char = 'a';
    int test_int = 32;
    float test_float = 1.414;
    std::string test_string = "hello world";
    std::vector<int> test_vector = {1,2,3};
    std::list<int> test_list = {4,5,6};
    std::set<int> test_set = {7,8,9};
    std::map<int,std::string> test_map = {{1,"how"},{2,"are"},{3,"you"}};

    // nested basic types
    std::pair<std::string,std::string> test_pair = {"happy birthday", "to you!"};
    std::vector<std::list<int>> test_v_l = {{2,6,8,45,6},{898,7787,5454}};
    std::map<std::vector<int>,std::string> test_i_m = {{test_vector,"first is here"},\
                                                {{7,45,88,954,}, "this is the second"}};
    std::list<std::vector<int>> test_l_v = {{2,6,8,45,6},{898,7787,5454}};
    std::set<std::list<int>> test_s_l = {{2,6,8,45,6},{898,7787,5454}};
```
Note: **The program is coded in the way where in theory, any combination and any nested situation of data types can be serialized and deserialized in either binary way or XML way.**

#### 2.2.2 User defined types

The program implements the support of user-defined types consists only of the basic types mentioned above in a way of static reflection.
All the user-defined types should be added a macro definition in format as follows:

```cpp
struct User_Define{};
DEFINE_STRUCT_SCHEMA(User_Define,
  DEFINE_STRUCT_FIELD(member1,"member1's name"),
  DEFINE_STRUCT_FIELD(member2,"member2's name"),
  DEFINE_STRUCT_FIELD(member3,"member3's name"),
  // ...
  DEFINE_STRUCT_FIELD(member4,"member4's name"));
```

- It supported a simple user defined type like:

```cpp
struct User{
        int id;
        int age;
        std::vector<std::string> gpa;
        std::map<int,float> sub;
};
DEFINE_STRUCT_SCHEMA(User,
  DEFINE_STRUCT_FIELD(id,"id"),
  DEFINE_STRUCT_FIELD(age,"age"),
  DEFINE_STRUCT_FIELD(gpa,"gpa"),
  DEFINE_STRUCT_FIELD(sub,"sub"));
              
```
- Also, a nested user defined type is supported, here is a sample struct :

```cpp

struct Demo{
    int id;
    float ratio;
    std::string name;
    std::vector<std::string> token;
    User cases;           // note that here a member type is alse user defined
};
DEFINE_STRUCT_SCHEMA(Demo,
  DEFINE_STRUCT_FIELD(id,"id"),
  DEFINE_STRUCT_FIELD(ratio,"ratio"),
  DEFINE_STRUCT_FIELD(name,"name"),
  DEFINE_STRUCT_FIELD(token,"token"),
  DEFINE_STRUCT_FIELD(cases,"cases"));

```

### 2.3 Main Framework
The project has mainly two parts and both have no dependency of each other.

#### 2.3.1 Binary serialization and deserialization
For Binary part, the binary serialized data is stored in a char array before it is written to a file. The `src/include/Buffer.h` file contains the I/O part of the project, so it will not be described in detail here.

The upper abstraction is in `namespace binary`. It provides the following functions: `binary::serialize` and `binary::deserialize`. In both, the objects are transfered to binary format and then written to a file.

The serialized data is transferd by Class `Seel`, which later is also responsible for the deserialization:

The member variants of `Seel` are:

```cpp
    Type return_type;       // the class type it should return when deserialized
    int32_t meta_num;       // the total number of elements
    size_t atom_size;       // the size of atomic elements
    char* data_;            // binary of the object
```

Here atomic elements means those types that can not be cut to smaller conponents, e.g., `int` and `char` are atomic, but `std::string` and STL containers like `std::vector<>` are not. `data_` is what stores the object we want to serialize and is also what we want to deserialize from later on.
Apart from `data_`, other three data members are metadata used to indicate the deserialization process.
For atomic types, `data_` is simply a binary data recieved by `memcpy` from the object. For non-atomic types, `data_` is exactly what each of its conponents is serialized to file. If the conponent of a non-atomic type is also a non-atomic type, then do it recursively.
To write the data to file, `Buffer::writebin(const Seel& )` is provided. It first writes the metadata to the file, then writes the binary data to the file.

When it come to deserialization, the `Buffer::readbin(Seel&)` is used to read the metadata from the file, then reads the binary data from the file and assign it to `Seel::data_`. `Seel::writeback(T& )` then deserializes the binary data to the object. The deserialization process is similar to the serialization process, to deserialize the non-atomic types, a recursive process is essential: `Seel::deserialized_frombytes(char* )` is used to deseialize the sub-objects from father's `data_`.




#### 2.3.2 XML serialization and deserialization
Based on the Binary way methods, XML serialization is quite similar. `namespace xml` and `namespace SeelXML` deals with the upper abstraction and the core implementations. All the values are stored in the Nodes isolatedly.
A sample output of the program, `Demo` and `User` are user-defined types:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<Serializer>
    <Demo>
        <int value="1"/>
        <float value="3.1415927"/>
        <string value="Pass test!"/>
        <std_vector>
            <string value="item[1]"/>
            <string value="item[2]"/>
            <string value="item[3]"/>
        </std_vector>
        <User>
            <int value="3200"/>
            <int value="99"/>
            <std_vector>
                <string value="good"/>
                <string value="second"/>
            </std_vector>
            <std_map/>
        </User>
    </Demo>
</Serializer>
```
To serialize a object, program first check if it's atom type. If so, open a child-node and store it, otherwise, open a child-node and shifts to it and serialize all its conponents recursively.

## 3 Core Techniques

***

### Reflection

To implement the support of any user-defined type, a simple reflection mechanism is needed. This program has a simple static reflection mechanism that not affecting the run-time performance.

#### Eleminated implementation

To implement a static reflection function, I first tried a totally based on macro way, namely insert functions into user-defined types like:
```cpp
struct Demo{
    REFLECTION(
        (int),id,
        (float), ratio,
        (std::map<int,std::string>), mapping
    );
}
// is processed into
struct Demo{
    int id;
    float  ratio;
    std::map<int,std::string>  mapping;

    int& _FUN1(){return id;}
    float& _FUN2(){return ratio;}
    std::map<int,std::string>& _FUN3(){return mapping;}
    bool& _FUN4(){throw "member not found!" return _GLOBAL_BOOL;}
    bool& _FUN5(){throw "member not found!" return _GLOBAL_BOOL;}
    \\...

    bool& _FUN16(){throw "member not found!" return _GLOBAL_BOOL;}

}

```
By using `#define FUN(T) _FUN##T()` macro, we can get the reference of a struct's member variants:

```cpp
Demo test;
test.FUN(1) = 32000;
```

All the code of the mentioned way is in `src/dumped/include`.
<font color="red">
Due to three unavoidable drawbacks, the above way is dumped:
1. The number of reflected member variants are limited due to the way I organized the macro. The upper boundray I set is 16, and once more is needed, I have to add the number list manually.
2. Since the `FUN()` is a macro, it's processed way before run-time, even before compile time, because of which, a dynamic way of accessing is impossible, there is no way I can `demo.FUN(i)` where `i` is a number in run-time.
3. The macro actually defines some member funcitons in the struct that user defined, which is hidden in the back stage.
</font>

```cpp
int member = demo._GETINFO()->member_number;
int step = 0;
if(0 == member)
    return ;
step+=serilize_node(demo.FUN(1),data_+step);
if(1 == member)
    return;
step+=serilize_node(demo.FUN(2),data_+step);
// ...
if(15 == member)
    return;
step+=serilize_node(demo.FUN(16),data_+step);
return ;
// awkward code is unavoidable!!
```

#### Current implementation

Due to the `std::integer_sequence` in `C++ 14`, a compiler-unfolding can be achieved.
Since a universal function can not return multi-types, the way we access the members is by member pointer and lambuda funtion, not returning the references of the members to the caller function, but to send the process funtion to the callee sub-routine.
Therefore a `std::tuple` is needed to store the member pointers, and since its a static data structure, to access it dynamicly, some tricks are needed.
The code is in `src/incldue/Reflection.h`.

```cpp
namespace detail {

template <typename Fun, typename Tuple, std::size_t... I>
inline constexpr void ForEachTuple(Tuple&& tuple,
                                   Fun&& fun,
                                   std::index_sequence<I...>) {
     std::initializer_list<int>{(fun(std::get<I>(tuple),I), 0)...};

}

template <typename Fun, typename Tuple>
inline constexpr void ForTuple(Tuple&& tuple, Fun&& fun) {
  ForEachTuple(tuple, fun, std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
}

// struct_schema<T> is the tuple of the struct T

}
template <typename T, typename Fn>
inline void ForField(T& object, int i, Fn&& fn) {
  detail::ForTuple(struct_schema<T>,
  [&object, &fn, &i](auto&& field_schema, int j) {
    if(j == i)
        fn(object.*(std::get<0>(field_schema)), std::get<1>(field_schema));
    else
        return;
  }
  );
}
```

In this way, a dynamic index is used to access the member of the struct, in a static way.

### Template Metaprogram
To get the objects' type and to judge if a class is a user-defined type, template metaprogram technique is massively used.

```cpp
// get the type of the object, is registered when user-defined type is defined
template<typename T, typename... type>
struct _is_valid_type
{
    static const Type id = OTHER;
    static const char offset = 0;
    
};

template<typename T,typename... Types>
constexpr Type is_valid_type = _is_valid_type<T, Types...>::id;
/**/


// get the name of the object, is registered when user-defined type is defined
template <typename T>
constexpr auto ClassName(){return "Not_Userdefined_type";}

template <>
struct is_user_defined<Struct> : std::true_type {};

template <>
constexpr auto ClassName<Struct>(){return #Struct;}

```

Detailed information is in `src/incldue/Reflection.h` and `src/incldue/TypeFigure.h`.





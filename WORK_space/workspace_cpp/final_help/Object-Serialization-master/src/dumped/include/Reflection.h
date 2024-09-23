#ifndef USER_DEFINED_H
#define USER_DEFINED_H
#include <string>
#include <vector>
#include <map>
//#include "Seel.h"
#include "Typefigure.h"
#include "MACRO_EX.h"
#define TOSTRING(type) #type



#define ADD_META                            std::string name;                                                       \
                                            short members;                                                          \
                                            std::vector<std::string> member_names;                                  \
                                            std::vector<Type> member_types

#define ArgCount(...) _ArgCount(__VA_ARGS__, 16,16, 15,15, 14,14, 13,13, 12,12, 11,11, 10,10, 9,9, 8,8, 7,7, 6,6, 5,5, 4, 4, 3,3, 2,2, 1, 1)
#define _ArgCount(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26,_27,_28,_29,_30,_31, COUNT, ...) COUNT

template <typename T>
struct struct_schema{
    static constexpr int value = 0;
};


#define _WRAP(T, ...) PUSH_FIELDS_##T(__VA_ARGS__)


#define REFLECT(_structname, ...)           EXPAND_DEFINE(ArgCount(__VA_ARGS__), __VA_ARGS__)                       \
                                            static constexpr int value = ArgCount(__VA_ARGS__);                     \
                                            TypeInfo _GETINFO()const{                                               \
                                            TypeInfo temp;                                                          \
                                            unsigned int offset = 0;                                                \
                                            temp.members = ArgCount(__VA_ARGS__);                                   \
                                            temp.name = TOSTRING(_structname);                                      \
                                            PUSH_FIELDS(ArgCount(__VA_ARGS__),__VA_ARGS__)                          \
                                            return temp;}
                                            

struct TypeInfo{
    std::string name;
    short members;
    std::vector<std::string> member_names;
    std::vector<Type> member_types;
    std::vector<unsigned int> offset;
};

struct User_sub{
    User_sub(){check = 1;}
    ~User_sub(){}
    bool operator==(const User_sub& rhs){
        return (check == rhs.check);
    }
    REFLECT(User_sub,
            (float) , check);


        
            
 

};





template <typename U>
struct is_user_defined{
    
    template <typename T, TypeInfo(T::*)() const = &T::_GETINFO>
    static constexpr bool check(T*) { return true; };   //  (1)
    static constexpr bool check(...) { return false; }; //  (2)
 
    static constexpr bool ret = check(static_cast<U*>(0));  //  (3)
};



#endif
/*
#ifndef REFLECT_H
#define REFLECT_H

#include <tuple>
#include <type_traits>

namespace detail {

template <typename Fun, typename Tuple, std::size_t... I>
inline constexpr void ForEachTuple(Tuple&& tuple,
                                   Fun&& fun,
                                   std::index_sequence<I...>) {
     std::initializer_list<int>{(fun(std::get<I>(tuple),I), 0)...};

}

template <typename Fun, typename Tuple>
inline constexpr void ForEachTuple(Tuple&& tuple, Fun&& fun) {
  ForEachTuple(tuple, fun, std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
}


}  // namespace detail


template <typename T>
inline constexpr auto StructSchema() {
  return std::make_tuple();
}
template <typename U>
struct is_user_defined : std::false_type{};

template <typename T>
constexpr auto ClassName(){return "Not_Userdefined_type";}





#define DEFINE_STRUCT_SCHEMA(Struct, ...)             \
  template <>                                         \
  inline constexpr auto StructSchema<Struct>() {      \
    using _Struct = Struct;                           \
    return std::make_tuple(__VA_ARGS__);              \
  }                                                   \
  template <>                                         \
  struct is_user_defined<Struct> : std::true_type {}; \
  template <>                                         \
  constexpr auto ClassName<Struct>(){return #Struct;}


#define DEFINE_STRUCT_FIELD(StructField, FieldName) \
  std::make_tuple(&_Struct::StructField, FieldName)



template <typename T>
constexpr auto struct_schema = StructSchema<std::decay_t<T>>();

template <typename T, typename Fn>
inline void ForEachField(T&& value, int i, Fn&& fn) {
  detail::ForEachTuple(struct_schema<T>, 
  [&value, &fn, &i](auto&& field_schema, int j) {
    if(j == i)
        fn(value.*(std::get<0>(field_schema)), std::get<1>(field_schema));
    else
        return;
  }
  );
}






#endif
*/
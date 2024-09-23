#ifndef TYPEFIGURE_H
#define TYPEFIGURE_H
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <type_traits>

enum Type{
    KEEP,
    OTHER,
    BOOL,
    INT,
    FLOAT,
    CHAR,
    STRING,
    PAIR,
    VECTOR,
    LIST,
    SET,
    MAP
    
};
struct _KEEP{
    ;
};

template<typename T, typename... type>
struct _is_valid_type
{
    static const Type id = OTHER;
    static const char offset = 0;
    
};
template<>
struct _is_valid_type<_KEEP>
{
    static const Type id = KEEP;
    static const char offset = 0;
    //static const int8_t size = 1;
};
template<>
struct _is_valid_type<bool>
{
    static const Type id = BOOL;
    static const char offset = 1;
    //static const int8_t size = 1;
};
template<>
struct _is_valid_type<int>
{
    static const Type id = INT;
    static const char offset = sizeof(int);
    //static const int8_t size = 4;
};
template<>
struct _is_valid_type<float>
{
    static const Type id = FLOAT;
    static const char offset = sizeof(float);
    //static const int8_t size = 4;
};
template<>
struct _is_valid_type<char>
{
    static const Type id = CHAR;
    static const char offset = 1;
};
template<>
struct _is_valid_type<std::string>
{
    static const Type id = STRING;
    static const char offset = sizeof(std::string);
};






template<typename T, typename... type>
struct _is_valid_type<std::pair<T,type...>>
{
    static const Type id = PAIR;
    static const char offset = sizeof(std::pair<T,type...>);
};

template<typename T, typename... type>
struct _is_valid_type<std::vector<T,type...>>
{
    static const Type id = VECTOR;
    static const char offset = sizeof(std::vector<T,type...>);
};

template<typename T, typename... type>
struct _is_valid_type<std::list<T,type...>>
{
    static const Type id = LIST;
    static const char offset = sizeof(std::list<T,type...>);
};
template<typename T, typename... type>
struct _is_valid_type<std::set<T,type...>>
{
    static const Type id = SET;
    static const char offset = sizeof(std::set<T,type...>);
};
template<typename T, typename... type>
struct _is_valid_type<std::map<T,type...>>
{
    static const Type id = MAP;
    static const char offset = sizeof(std::map<T,type...>);
};


template<typename T,typename... Types>
constexpr Type is_valid_type = _is_valid_type<T, Types...>::id;

template<typename T,typename... Types>
constexpr char is_valid_type_offset = _is_valid_type<T, Types...>::offset;


#endif
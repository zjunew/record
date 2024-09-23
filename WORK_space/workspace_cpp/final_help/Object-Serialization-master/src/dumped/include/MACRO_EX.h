#ifndef MACRO_EX_H
#define MACRO_EX_H
#include "Typefigure.h"
#include <type_traits>

/*
template <typename T>
T Checks(T& src){return src; }

int Checks() {return 0; }
*/

int _GLOBALD = 0;
bool _OUT_OF_RANGE = false;
#define Checks(...) _Checks(temp,##__VA_ARGS__,_GLOBALD)
#define _Checks(T,K, ...) K

#define CHECKS(...) _CHECKS((int),##__VA_ARGS__,(int))
#define _CHECKS(T, K, ...) _D_PARSE K
#define _D_PARSE(...) __VA_ARGS__

#define EXPAND_DEFINE(T, ...) _D_EXPAND_DEFINE_(T, __VA_ARGS__)
#define _D_EXPAND_DEFINE_(T, ...) _EXPAND_DEFINE_##T(1,__VA_ARGS__) _S_EXPAND_UPPER(ADD_##T)

#define _S_EXPAND_UPPER(N) _SS_EXPAND_UPPER_(N)
#define _SS_EXPAND_UPPER_(N) _EXPAND_UPPER_##N

//_EXPAND_DEFINE_0(__VA_ARGS__, , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , ,)

#define _EXPAND_DEFINE_16(N,COUT12,COUT13, ...)      _D_PARSE COUT12 COUT13;      CHECKS(COUT12)&  _FUN##N() {int temp = 0;return Checks(COUT13);} _S_EXPAND_DEFINE_15(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_15(N,COUT0,COUT1, ...)        _D_PARSE COUT0 COUT1;        CHECKS(COUT0)&   _FUN##N() {int temp = 0;return Checks(COUT1);} _S_EXPAND_DEFINE_14(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_14(N,COUT2,COUT3, ...)        _D_PARSE COUT2 COUT3;        CHECKS(COUT2)&   _FUN##N() {int temp = 0;return Checks(COUT3);} _S_EXPAND_DEFINE_13(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_13(N,COUT4,COUT5, ...)        _D_PARSE COUT4 COUT5;        CHECKS(COUT4)&   _FUN##N() {int temp = 0;return Checks(COUT5);} _S_EXPAND_DEFINE_12(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_12(N,COUT6,COUT7, ...)        _D_PARSE COUT6 COUT7;        CHECKS(COUT6)&   _FUN##N() {int temp = 0;return Checks(COUT7);} _S_EXPAND_DEFINE_11(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_11(N,COUT8,COUT9, ...)        _D_PARSE COUT8 COUT9;        CHECKS(COUT8)&   _FUN##N() {int temp = 0;return Checks(COUT9);} _S_EXPAND_DEFINE_10(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_10(N,COUT10,COUT11, ...)      _D_PARSE COUT10 COUT11;      CHECKS(COUT10)&  _FUN##N() {int temp = 0;return Checks(COUT11);} _S_EXPAND_DEFINE_9(ADD_##N,__VA_ARGS__)

#define _EXPAND_DEFINE_9(N,COUT14,COUT15, ...)      _D_PARSE COUT14 COUT15;      CHECKS(COUT14)&  _FUN##N() {int temp = 0;return Checks(COUT15);} _S_EXPAND_DEFINE_8(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_8(N,COUT16,COUT17, ...)      _D_PARSE COUT16 COUT17;      CHECKS(COUT16)&  _FUN##N() {int temp = 0;return Checks(COUT17);} _S_EXPAND_DEFINE_7(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_7(N,COUT18,COUT19, ...)      _D_PARSE COUT18 COUT19;      CHECKS(COUT18)&  _FUN##N() {int temp = 0;return Checks(COUT19);} _S_EXPAND_DEFINE_6(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_6(N,COUT20,COUT21, ...)      _D_PARSE COUT20 COUT21;      CHECKS(COUT20)&  _FUN##N() {int temp = 0;return Checks(COUT21);} _S_EXPAND_DEFINE_5(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_5(N,COUT22,COUT23, ...)      _D_PARSE COUT22 COUT23;      CHECKS(COUT22)&  _FUN##N() {int temp = 0;return Checks(COUT23);} _S_EXPAND_DEFINE_4(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_4(N,COUT24,COUT25, ...)      _D_PARSE COUT24 COUT25;      CHECKS(COUT24)&  _FUN##N() {int temp = 0;return Checks(COUT25);} _S_EXPAND_DEFINE_3(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_3(N,COUT26,COUT27, ...)      _D_PARSE COUT26 COUT27;      CHECKS(COUT26)&  _FUN##N() {int temp = 0;return Checks(COUT27);} _S_EXPAND_DEFINE_2(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_2(N,COUT28,COUT29, ...)      _D_PARSE COUT28 COUT29;      CHECKS(COUT28)&  _FUN##N() {int temp = 0;return Checks(COUT29);} _S_EXPAND_DEFINE_1(ADD_##N,__VA_ARGS__)
#define _EXPAND_DEFINE_1(N,COUT30,COUT31, ...)      _D_PARSE COUT30 COUT31;      CHECKS(COUT30)&  _FUN##N() {int temp = 0;return Checks(COUT31);}
#define _EXPAND_DEFINE_(...) __VA_ARGS__

#define _S_EXPAND_DEFINE_1(T, ...) _EXPAND_DEFINE_1(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_2(T, ...) _EXPAND_DEFINE_2(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_3(T, ...) _EXPAND_DEFINE_3(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_4(T, ...) _EXPAND_DEFINE_4(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_5(T, ...) _EXPAND_DEFINE_5(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_6(T, ...) _EXPAND_DEFINE_6(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_7(T, ...) _EXPAND_DEFINE_7(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_8(T, ...) _EXPAND_DEFINE_8(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_9(T, ...) _EXPAND_DEFINE_9(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_10(T, ...) _EXPAND_DEFINE_10(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_11(T, ...) _EXPAND_DEFINE_11(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_12(T, ...) _EXPAND_DEFINE_12(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_13(T, ...) _EXPAND_DEFINE_13(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_14(T, ...) _EXPAND_DEFINE_14(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_15(T, ...) _EXPAND_DEFINE_15(T,__VA_ARGS__)
#define _S_EXPAND_DEFINE_16(T, ...) _EXPAND_DEFINE_16(T,__VA_ARGS__)


#define _EXPAND_UPPER_1 bool& _FUN1() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_2
#define _EXPAND_UPPER_2 bool& _FUN2() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_3
#define _EXPAND_UPPER_3 bool& _FUN3() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_4
#define _EXPAND_UPPER_4 bool& _FUN4() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_5
#define _EXPAND_UPPER_5 bool& _FUN5() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_6
#define _EXPAND_UPPER_6 bool& _FUN6() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_7
#define _EXPAND_UPPER_7 bool& _FUN7() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_8
#define _EXPAND_UPPER_8 bool& _FUN8() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_9
#define _EXPAND_UPPER_9 bool& _FUN9() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_10
#define _EXPAND_UPPER_10 bool& _FUN10() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_11
#define _EXPAND_UPPER_11 bool& _FUN11() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_12
#define _EXPAND_UPPER_12 bool& _FUN12() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_13
#define _EXPAND_UPPER_13 bool& _FUN13() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_14
#define _EXPAND_UPPER_14 bool& _FUN14() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_15
#define _EXPAND_UPPER_15 bool& _FUN15() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} _EXPAND_UPPER_16
#define _EXPAND_UPPER_16 bool& _FUN16() {throw std::out_of_range("has no method it points to"); return _OUT_OF_RANGE;} 


#define FUN(i) _FUN##i()

#define ADD_1 2
#define ADD_2 3
#define ADD_3 4
#define ADD_4 5
#define ADD_5 6
#define ADD_6 7
#define ADD_7 8
#define ADD_8 9
#define ADD_9 10
#define ADD_10 11
#define ADD_11 12
#define ADD_12 13
#define ADD_13 14
#define ADD_14 15
#define ADD_15 16


#define PUSH_FIELDS(N, ...) _P_FILEDS(N,__VA_ARGS__)

#define _P_FILEDS(N, ...)         PUSH_FIELDS_##N(__VA_ARGS__,_KEEP,_KEEP,_KEEP,_KEEP,_KEEP,_KEEP,_KEEP,                     \
                                    _KEEP,_KEEP,_KEEP,_KEEP,_KEEP,_KEEP,_KEEP,_KEEP,_KEEP,_KEEP,_KEEP,                       \
                                    _KEEP,_KEEP ,_KEEP ,_KEEP , _KEEP, _KEEP, _KEEP, _KEEP, _KEEP,_KEEP,                     \
                                    _KEEP,_KEEP,_KEEP,_KEEP,_KEEP)

#define PUSH_FIELDS_16(COUT30,COUT31, ...)        temp.member_types.push_back(is_valid_type<_D_PARSE COUT30>);    temp.member_names.push_back(#COUT31);  temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT30>;     PUSH_FIELDS_15(__VA_ARGS__)
#define PUSH_FIELDS_15(COUT28,COUT29, ...)        temp.member_types.push_back(is_valid_type<_D_PARSE COUT28>);    temp.member_names.push_back(#COUT29);  temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT28>;     PUSH_FIELDS_14(__VA_ARGS__)
#define PUSH_FIELDS_14(COUT26,COUT27, ...)        temp.member_types.push_back(is_valid_type<_D_PARSE COUT26>);    temp.member_names.push_back(#COUT27);  temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT26>;     PUSH_FIELDS_13(__VA_ARGS__)
#define PUSH_FIELDS_13(COUT24,COUT25, ...)        temp.member_types.push_back(is_valid_type<_D_PARSE COUT24>);    temp.member_names.push_back(#COUT25);  temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT24>;     PUSH_FIELDS_12(__VA_ARGS__)
#define PUSH_FIELDS_12(COUT22,COUT23, ...)        temp.member_types.push_back(is_valid_type<_D_PARSE COUT22>);    temp.member_names.push_back(#COUT23);  temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT22>;     PUSH_FIELDS_11(__VA_ARGS__)
#define PUSH_FIELDS_11(COUT20,COUT21, ...)        temp.member_types.push_back(is_valid_type<_D_PARSE COUT20>);    temp.member_names.push_back(#COUT21);  temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT20>;     PUSH_FIELDS_10(__VA_ARGS__)
#define PUSH_FIELDS_10(COUT18,COUT19, ...)        temp.member_types.push_back(is_valid_type<_D_PARSE COUT18>);    temp.member_names.push_back(#COUT19);  temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT18>;     PUSH_FIELDS_9(__VA_ARGS__)
#define PUSH_FIELDS_9(COUT16,COUT17, ...)         temp.member_types.push_back(is_valid_type<_D_PARSE COUT16>);    temp.member_names.push_back(#COUT17);  temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT16>;     PUSH_FIELDS_8(__VA_ARGS__)
#define PUSH_FIELDS_8(COUT14,COUT15, ...)         temp.member_types.push_back(is_valid_type<_D_PARSE COUT14>);    temp.member_names.push_back(#COUT15);  temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT14>;     PUSH_FIELDS_7(__VA_ARGS__)
#define PUSH_FIELDS_7(COUT12,COUT13, ...)         temp.member_types.push_back(is_valid_type<_D_PARSE COUT12>);    temp.member_names.push_back(#COUT13);  temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT12>;     PUSH_FIELDS_6(__VA_ARGS__)
#define PUSH_FIELDS_6(COUT10,COUT11, ...)         temp.member_types.push_back(is_valid_type<_D_PARSE COUT10>);    temp.member_names.push_back(#COUT11);  temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT10>;     PUSH_FIELDS_5(__VA_ARGS__)
#define PUSH_FIELDS_5(COUT8,COUT9, ...)           temp.member_types.push_back(is_valid_type<_D_PARSE COUT8>);     temp.member_names.push_back(#COUT9);   temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT8>;     PUSH_FIELDS_4(__VA_ARGS__)
#define PUSH_FIELDS_4(COUT6,COUT7, ...)           temp.member_types.push_back(is_valid_type<_D_PARSE COUT6>);     temp.member_names.push_back(#COUT7);   temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT6>;     PUSH_FIELDS_3(__VA_ARGS__)
#define PUSH_FIELDS_3(COUT4,COUT5, ...)           temp.member_types.push_back(is_valid_type<_D_PARSE COUT4>);     temp.member_names.push_back(#COUT5);   temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT4>;     PUSH_FIELDS_2(__VA_ARGS__)
#define PUSH_FIELDS_2(COUT2,COUT3, ...)           temp.member_types.push_back(is_valid_type<_D_PARSE COUT2>);     temp.member_names.push_back(#COUT3);   temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT2>;     PUSH_FIELDS_1(__VA_ARGS__)
#define PUSH_FIELDS_1(COUT0,COUT1, ...)           temp.member_types.push_back(is_valid_type<_D_PARSE COUT0>);     temp.member_names.push_back(#COUT1);   temp.offset.push_back(offset);   offset+=is_valid_type_offset<_D_PARSE COUT0>;

#define RECORD_FUNCS(NAME)      temp.func[0] = &NAME::_FUN0;        temp.func[1] = &NAME::_FUN1;        temp.func[2] = &NAME::_FUN2;        temp.func[3] = &NAME::_FUN3;    \
                                temp.func[4] = &NAME::_FUN4;        temp.func[5] = &NAME::_FUN5;        temp.func[6] = &NAME::_FUN6;        temp.func[7] = &NAME::_FUN7;    \
                                temp.func[8] = &NAME::_FUN8;        temp.func[9] = &NAME::_FUN9;        temp.func[10] = &NAME::_FUN10;      temp.func[11] = &NAME::_FUN11;  \
                                temp.func[12] = &NAME::_FUN12;      temp.func[13] = &NAME::_FUN13;      temp.func[14] = &NAME::_FUN14;      temp.func[15] = &NAME::_FUN15;

template <int N>
struct Getmember{
    ;
};

template <>
struct Getmember<1>{
    template <typename U>
    static auto value(U& src){
        return src.FUN(1);
    }
};






#endif
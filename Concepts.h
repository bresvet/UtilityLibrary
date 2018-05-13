//
// Created by bs on 29.01.18.
//
#ifndef DAFFODIL_CONCEPTS_H
#define DAFFODIL_CONCEPTS_H

template<typename ...>
using VoidT=void;

template<bool B>
struct BoolConstant
{
    static auto value=BoolConstant<B>::val;
    static constexpr auto val=value;
};

using TrueType=BoolConstant<true>;
using FalseType=BoolConstant<false>;

template<typename...>
struct Conjunction : std::true_type {};

template<typename B1>
struct Conjunction<B1> : B1 { };

template<typename B1, typename... Bn>
struct Conjunction<B1, Bn...>
        : std::conditional_t<bool(B1::value),Conjunction<Bn...>,B1>{};

template<typename...>
struct Alternative:std::true_type{};

template<typename B1>
struct Alternative<B1>:public B1{};

template<typename B1,typename...Bn>
struct Alternative<B1,Bn...>:public std::conditional_t<B1::value,std::true_type,Alternative<Bn...>>{};

template<typename B1>
struct Negation:public std::conditional_t<B1::value,std::false_type,std::true_type>{};


template<typename...>
using VoidT=void;

template<typename,typename=VoidT<>>
struct isIterator:public std::false_type{};

template<typename I>
struct isIterator<I,VoidT<Conjunction<typename I::value_type,typename I::difference_type
        ,typename I::pointer,typename I::reference>>>:public std::true_type{};

#include<type_traits>
#include<utility>
#include<string>
#include<typeinfo>
namespace CrystalAmpoule
{
 #define HAS_MEMBER_NAMED(memname)\
\
template<typename,typename=VoidT<>>\
struct hasMemberNamed_##memname:public std::false_type\
{ };\
template<typename T>\
struct hasMemberNamed_##memname<T,VoidT<decltype(std::declval<T>().mem_name)>>:public std::true_type\
{};\
template<typename T>\
constexpr bool hasMemberNamed_##memname_value=hasMemberNamed_##memname<T>::value;\


    template<typename, typename=VoidT<>>
    struct isComparable : public std::false_type
    {

    };

    template<typename T>
    struct isComparable<T, VoidT<decltype(std::declval<T>() < std::declval<T>())>> : public std::true_type
    {

    };


//walkaround implementation


    template<typename...>
    using VoidT=void;

   template<typename, typename=VoidT>
    struct isTemplateClass : public std::false_type
    {

    };

    template<template<typename...>typename C>
    struct isTemplateClass<C,VoidT<decltype(std::declval<C<...>>())>> : public std::true_type
    {

    };


    template<template<typename...>typename T>
    struct isTemplateClass
    {
        static constexpr auto value=[](auto...P)->decltype(T<P...>){};
    };

    template<typename, typename, typename=VoidT<>>
    struct hasMemberOfType : public std::false_type {

    };

    template<typename C, typename T>
    struct hasMemberOfType<C, VoidT<typename C::T>> : public std::true_type {

    };


    template<typename, typename=VoidT<>>
    struct isAlternativelyComparableByMember : public std::false_type {

    };


/*
    template<typename, typename=VoidT<>>
    struct isContainer : public std::false_type {

    };

    template<typename T, typename A=>
    struct isContainer<T, decltyp
            {

            };


   template<typename T>
    struct isDeprecated<>
    {

    };
*/


  /*  template<typename T>
    struct isLiteralType<>
    {

    };
*/

  template<typename,typename=VoidT<>>
  struct isSingleton:public std::false_type
  {

  };

    template<typename T,typename TPTR=T*,typename=std::enable_if<CrystalAmpoule::hasMemberOfType<T,TPTR>::value>>
    struct isSingleton<T,VoidT<decltype(std::declval<T()>())>>:public std::true_type
  {

  };


    template<typename, typename=VoidT<>>
    struct isFunctor : public std::false_type
    {

    };

    template<typename T>
    struct isFunctor<T, decltype(std::declval<T()>())> : public std::true_type
    {

    };


    template<std::string s>
    struct typenameFromStringExists
    {
         using Type=void;
        static constexpr auto value =
                [](auto t)->decltype(auto)
                {
                    using Type=decltype(t);
                    return isValidTypenameFromString<decltype(t),s>::value;
                };
    };

    template<typename T,std::string s>
    struct isValidTypenameFromString
    {
        static constexpr auto value=typeid(std::decay_t<T>).name() == s;
    };




    template<typename F, typename...Arg, typename=VoidT<decltype(std::declval<F>()(std::declval<Arg &&>()...))>>
    std::true_type isValidImplementation(*void)
{

}

template<typename F, typename...Arg>
std::false_type isValidImplementation(...)
{

}

template<typename,typename...,typename=VoidT<>>
struct isValidTemplate:public std::false_type
{

};


template<typename T,typename...P>
struct isValidTemplate<T,P...,VoidT<decltype(std::declval<T>()<P...>)>>:public std::true_type
{

};

template<typename F,typename=std::enable_if_t<std::is_function<F>::value>>
struct functionReturn
{
    using Type=void;
    static constexpr decltype(auto) detectReturnType=[](auto r)->decltype(std::declval<F>()()){using Type=decltype(r);};
};



//walkaround implementation
/*
 * template<typename,typename,typename=VoidT<>>
struct isNothrowAnyCastable:public std::false_type
{

};
 template<typename T,typename A=std::any>
 struct isNothrowAnyCastableHelper<>

 template<typename T,typename A=std::any>
 struct isNothrowAnyCastable<T,A,VoidT<decltype(std::declval())>>:public std::bool_constant<noexcept<>>
{

};
 */

//alias templates

template<typename...>
using void_t=void;

template<std::string s>
using TypeFromString=CrystalAmpoule::typenameFromStringExists::Type;

template<typename F>
using TypeReturnedByFunction=functionReturn<F>::Type;

template<bool b>
struct BoolConstant
{
    using Type=BoolConstant<b>;
    static constexpr bool value = b;
};

template<typename T>
struct TypeT
{
    using Type=T;
};


template<typename T>
typename TypeT<T>::Type typeAsValue(TypeT<T>);

template<typename T>
constexpr bool isComparableValue = CrystalAmpoule::isComparable<T>::value;

template<typename T>
constexpr bool isAlternativelyComparableByMemberValue = CrystalAmpoule::isAlternativelyComparableByMember<T>::value;

template<typename C>
constexpr auto isTemplateClassValue = CrystalAmpoule::isTemplateClass<C>::value;

template<typename C, typename T>
constexpr bool hasMemberOfTypeValue = CrystalAmpoule::hasMemberOfType<C, T>::value;

template<typename T>
constexpr bool isSingletonValue = CrystalAmpoule::isSingleton<T>::value;

/*
template<typename T>
constexpr bool isContainerValue = CrystalAmpoule::isFunctor<T>::value;

template<typename T>
constexpr bool isDeprecatedValue = CrystalAmpoule::isDeprecated<T>::value;

template<typename T>
constexpr bool isLiteralTypeValue = CrystalAmpoule::isLiteralType<T>::value;

*/
template<typename T>
constexpr bool isFunctorValue = CrystalAmpoule::isFunctor<T>::value;

template<typename T,std::string s>
constexpr auto isValidTypenameFromStringValue = CrystalAmpoule::isValidTypenameFromString<T,s>::value;

template<typename T>
inline constexpr auto isValidCallValue = [](auto f) {return
        [](auto...arg) { return isValidImplementation<decltype(f), decltype(arg) &&...>(nullptr); }; };

}
#undef HAS_MEMBER_NAMED(memname)
#endif //DAFFODIL_CONCEPTS_H

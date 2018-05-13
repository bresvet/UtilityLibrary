//
// Created by bs on 02.01.18.
//
#include <type_traits>
#include <vector>

#ifndef DAFFODIL_TYPESPACK_H
#define DAFFODIL_TYPESPACK_H
namespace Daffodil
{
    template<template<typename I>class C,typename I=std::allocator<C>>
    struct inside_type
    {
        using Type=I;
    };

    template<template<typename I>class C,typename I=std::allocator<C>>//=std::enable_if_t<std::is_compound<C>>>
    struct ElementT
    {
     using Type=typename C::inside_type<C<I>>;
    };

    template<typename...T>
    class TypesPack
    {

    };

    template<typename List>
    class FrontT;

template<typename Head, typename...Tail>
class FrontT<TypesPack<Head,Tail...>>
{
public:
    using Type=Head;
};

template<typename List>
using Front=typename FrontT<List>::Type;

template<typename List>
class PopFrontT;

template<typename Head,typename...Tail>
class PopFrontT<TypesPack<Head,Tail...>>
{
public:
    using Type=TypesPack<Tail...>;
};

template<typename List>
using PopFront=typename PopFrontT<List>::Type;

    template<typename List,typename Element>
    class PushFrontT;

    template<typename...Elems,typename Element>
    class PushFrontT<TypesPack<Element,Elems...>,Element>
            {
    public:
        using Type=TypesPack<Element,Elems...>;

            };

    template<typename List,typename Element>
    using PushFront=typename PushFrontT<List,Element>::Type;


    template<typename List,unsigned N>
    class NthElementT<List,N>:public NthElementT<PopFront<List>,N-1>
    {

    };

    template<typename List>
    class isEmpty<List<>>:public std::false_type
    {

    };

    template<typename List>
    class isEmpty<>:public std::true_type
    {

    };
}
#endif //DAFFODIL_TYPESPACK_H

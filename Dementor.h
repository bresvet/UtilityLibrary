//
// Created by bs on 22.01.18.
//
#ifndef DAFFODIL_TYMAP_H
#define DAFFODIL_TYMAP_H

/*Real time sorted container with typename allowed as inside type allowed and allocator specified by type traits
 * Bartłomiej Światłoń*/
#include<iostream>
#include<cassert>
#include<type_traits>
#include<optional>
#include<exception>
#include<variant>
#include<memory>
#include<scoped_allocator>
#include<new>
#include<algorithm>
#include<utility>
#include<functional>

namespace CrystalAmpoule
{
    enum class ContainerError:unsigned
    {
       FAILED_CONSTRUCTION,
        FAILED_DESTRUCTION,
        OUT_OF_RANGE,
        BAD_ALLOC
    };

    template<template<typename>class C>
    struct ContainerException:virtual public std::exception
    {
    public:

        ContainerException()= default
        {

        }

        explicit constexpr ContainerException(ContainerError &cerror)noexcept
        :cerror(cerror)
        {

        }

        virtual ~ContainerException()noexcept
        {

        }


    protected:

        ContainerError cerror;

        void handle_cexpection_ptr(std::exception_ptr ceptr)
        {
            try
            {
                if(ceptr)
                {
                    std::rethrow_exception(ceptr);
                }
            }
            catch(std::exception &e)
            {
                std::cout<<"caught"<<e.what()<<std::endl;
            }
        }

        ContainerError getContainerError()const
        {
            return this->cerror;
        }


    };




    struct DementorException:public ContainerException
    {

    };

    template<typename T>
    struct Univallocator
    {

        using ValueType=T;
        using Iterator=T*;
        using ConstPointer=const T*;
        using SizeType=size_t;
        using PointerDifference=std::ptrdiff_t ;
        using LValueReference=T&;
        using RValueReference=T&&;
        using ConstLValueReference=const T&;

        Univallocator()= default;
        T *univallocate(size_t n)
        {
        if(n>std::size_t(-1)/sizeof(T)) throw std::bad_alloc();
            else return static_cast<T*>(std::malloc(n));
        }
        void univdeallocate(T* pointer)
        {
            std::free(pointer);
        }

        inline void create(const T&t,T *p)
        {
            new(p) T(t);
        }

        inline void destroy(T *p)
        {
            p->compl T();
        }

    };


    template<typename T,typename=std::enable_if_t<std::is_abstract<T>::value>>
    struct Univallocator:public std::pmr::polymorphic_allocator
    {
        Univallocator()= default;

    };

    template<template<typename T>class C,typename T=Univallocator<T>,typename=std::enable_if_t<std::is_array<C>::value>>
    struct Univallocator:public std::scoped_allocator_adaptor
    {

    };


    template<typename T,typename A=Univallocator<T>>
    struct DementorBase
    {
        A all;
        T *v;
        T *space;
        T *last;

        DementorBase()= default;

        DementorBase(const A&all,typename A::size_type n)
        try:all(all),v(all.univallocate(n)),space(v+n),last(v+n)
        {

        }
        catch(DementorException &de)
        {
            all.univdeallocate(n);
            throw;
        }
        ~DementorBase()
        {
           all.univdeallocate(v,last-v);
        }

        template<typename O,typename U=Univallocator<O>>
        void swap(const DementorBase<T>&deme,const DementorBase<O>&other)
        {

        };



    };


    template<typename T,typename A=Univallocator<T>>
    class DementorException:private std::exception
    {

    };

    template<typename T
            ,typename A=Univallocator<T>
            ,typename Cryt=std::function<void()>
            ,typename Pred=std::nullopt_t
            ,typename=std::enable_if_t<std::is_nothrow_destructible<T>::value && CrystalAmpoule::isComparable<T>::value>>

    class Dementor:private DementorBase<T,A>
    {
    private:

        Cryt cryterium;

        void destroy()
        {
            for(auto p=v;v!=space;p++)
            {
                p->compl T();
            }

        }

    public:

        constexpr explicit Dementor(size_t s,T &val=T(),const A &all=A(),
                                    Cryt cryterium=std::function<void()>)
                                         //   {std::sort(typename Dementor::Iterator B,typename Dementor::Iterator E,Pred predicate)})
        {
            try

            {
                v(all.univallocate(s));
            }

            catch(DementorException &de)
            {
                std::cout<<de.what()<<std::endl;
                throw;
            }
        }

        ~Dementor()
        {

        }

        Dementor(const Dementor &dem)
        {

        }

        Dementor(Dementor &&dem)
        {

        };

        Dementor &operator=(const Dementor &dem)
        {

        }

        Dementor &operator=(Dementor &&dem)
        {

        }

        Dementor &operator==(Dementor &deme)
        {

        }

        Dementor &operator!=(Dementor &deme)
        {

        }

        Dementor &operator+(Dementor &deme)
        {

        }

        Dementor &operator-(Dementor &deme)
        {

        }

        size_t getCapacity()const
        {
            return last-v;
        }

        size_t getSize()const
        {
            return space-v;
        }


        void push_back(T const &element)
        {

        }

        void pop_back(T const &element)
        {

        }

        decltype(auto) top





    };




}
#endif //DAFFODIL_TYMAP_H

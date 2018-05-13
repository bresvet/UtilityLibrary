//
// Created by bs on 29.01.18.
//
#ifndef DAFFODIL_DESIGNPATTERNS_H
#define DAFFODIL_DESIGNPATTERNS_H

#include <bits/shared_ptr.h>


#include <memory>
#include <type_traits>
#include "Concepts.h"

/* MUST BE DONE: Abstract Factory, Singleton, MVC,Bridge
 * ADDITIONAL CREATIONAL: Factory Method, Builder, Prototype,
 * STRUCTURAL : Adapter,  Composite, Decorator, Fasade, Flyweight, Proxy

 */

//ABSTRACT FACTORY

template<typename B,typename...D,typename=std::enable_if<Conjunction<std::is_abstract<B>,Conjunction<std::is_base_of<B,D>,...>>>
class Factory
{
    class AbstractFactory
    {
        public:

       template<typename...CArgs>
       virtual std::unique_ptr<B>create(CArgs &&...cargs)=0
       {
        return std::make_unique<B>(cargs...);
       }

     };

class ConcreteFactory final : public AbstractFactory
{
public:

    template<typename...CArgs>
    std::unique_ptr<D> create(CArgs&&...cargs)override
    {
        return std::make_unique<D>(cargs...);
    }
};

};

//SINGLETON

template<typename S,typename...CArgs>
class Singleton
{
public:

   static S& getInstance(CArgs&&...cargs)
   {
       if(!instance)
       {
           instance=std::make_unique(cargs...);
       }
       return *instance;
   }

   Singleton(const Singleton& sig)=delete;
   Singleton &operator=(const Singleton &sig)=delete;

protected:

    Singleton()= default;
    virtual ~Singleton()= default;


private:

inline static std::unique_ptr<S> instance;

};

//Model View Controller

/*
 * template<typename T>
class MVC
{
    class View
    {
    public:

        std::unique_ptr<T>actualModel;

        void update(const T& t)
        {
            *actualModel=t;
        }


    };

    class Controller
    {

        private:

        std::unique_ptr<T>model;
        std::unique_ptr<View>view;

    };
*/

//BRIDGE

template<typename A,typename I,typename...C,typename=std::enable_if<Conjunction<std::is_abstract<A>,Conjunction<std::is_base_of<A,C>,...>>>
class Bridge
{
public:

    class Interface:public A
    {
    protected:

        Impl &getImpl()
        {
            return *impl;
        }

    private:

        std::unique_ptr<Impl>impl;
    };

    class Impl:public I
    {
    protected:

        Impl()= default;
    };

    class Concrete:public Interface,virtual public C...
    {

    };

};

template<typename I,typename P,typename C,typename=std::enable_if<Conjunction<std::is_abstract<I>::value>>>
class Proxy
{
public:

    class Interface:public I
    {

    };

    class Proxy:public I
    {
    public:

        Interface *realInstance;
    };

    class Concrete:public I
    {

    };
};


template<typename I,typename P,typename...C,typename=std::enable_if<Conjunction<std::is_abstract<I>::value>>>
class Strategy
{

public:

    class StrategyInterface:public I
    {

    };

    class StrategyTest:public P
    {
    public:

        std::unique_ptr<StrategyInterface> strat;

    };

    class ConcreteStrategy:public I,virtual public C...
    {

    };

};

template<typename B,typename...H,typename=std::enable_if<Conjunction<std::is_abstract<B>::value,Conjunction<std::is_base_of<B,H>,...>>>
class Chain
{
    public:

    class Base:public B
    {
    public:

        Base *next;

        Base()
        {
            next = nullptr;
        }

        void setNext(Base *n)
        {
            next = n;
        }

        void add(Base *n)
        {
            if (next)
                next->add(n);
            else
                next = n;
        }

        virtual void handle(int i)
        {
            next->handle(i);
        }
    };

    class Handler:public B,virtual public H...
    {

    };
};


template<typename A,typename...C,typename=std::enable_if<Conjunction<std::is_abstract<A>,Conjunction<std::is_base_of<A,C>,...>>>
class Facade
{
    public:

    std::unique_ptr<Factory<A>>abstractMaker;
};





#endif //DAFFODIL_DESIGNPATTERNS_H

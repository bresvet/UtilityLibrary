//
// Created by bs on 29.01.18.
//
#ifndef DAFFODIL_COMPILETIMECOMPUTATIONS_H
#define DAFFODIL_COMPILETIMECOMPUTATIONS_H

#include<utility>
#include<algorithm>

namespace CrystalAmpoule
{
template<typename T,T a,T n,typename I=std::make_integer_sequence<T,n>>
struct compileTimePower
{

};

template<typename T,T a,T n,T...Is>
struct compileTimePower<T,a,n,std::integer_sequence<T,Is...>>
{
static constexpr T value=(static_cast<T>(1))*....*(a*static_cast<T>(Is+1));
};



template<typename T,T a,T n,typename I=std::make_integer_sequence<T,n>>
struct compileTimeRoot
{

};

template<typename T=double,T a,T n,T...Is,typename V=std::vector<T>,typename I=typename V::iterator>
struct compileTimeRoot<T,a,n,std::integer_sequence<T,Is...>>
{
static V v;
static auto which;
static  decltype(auto) find(I start=v.begin(),I finish=v.end())
{
    v.push_back((Is / n)...);
    which = std::find_if(v.begin(), v.end(), [&](const T &t1, const T &t2)
            -> bool { CrystalAmpoule::compileTimePower<T, t1, n>::value < a
                      && CrystalAmpoule::compileTimePower<T, t2, n>::value > a;});
    CrystalAmpoule::compileTimeRoot::find(which,which+1);
}

static constexpr auto value=(*which+*(which++)/2);

//compileTimeRoot<decltype(std::declval<decltype(which)>()+std::declval<decltype(which++)>())
// ,which*(which+static_cast<decltype(std::declval<decltype(which)>()+std::declval<decltype(which++)>())>(1)),2>::value;

};





template<typename T,T a,T n>
constexpr auto compileTimeRootValue=CrystalAmpoule::compileTimeRoot<T,a,n>::value;

template<typename T,T a,T n>
constexpr auto compileTImePowerValue=CrystalAmpoule::compileTimePower<T,a,n>::value;
}
#endif //DAFFODIL_COMPILETIMECOMPUTATIONS_H

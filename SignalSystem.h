//
// Created by bs on 15.02.18.
//

#ifndef CRYSTALAMPOULE_SIGNALSYSTEM_H
#define CRYSTALAMPOULE_SIGNALSYSTEM_H

#include<iostream>
#include<functional>
#include<type_traits>


template<typename F,typename=std::enable_if<std::is_function<F>::value>>
class Signal:public std::function
{

};

template<typename F,typename=std::enable_if<std::is_function<F>::value>>
class Slot:public std::function
{

};

template<template<typename...PROD>typename,template<typename...RECI>typename,typename=std::enable_if<>
void conjuct(PROD...prod,)
#endif //CRYSTALAMPOULE_SIGNALSYSTEM_H

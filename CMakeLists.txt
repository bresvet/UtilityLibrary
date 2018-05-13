cmake_minimum_required(VERSION 3.9)
project(CrystalAmpoule)

set(CMAKE_CXX_STANDARD 17)

add_library(CrystalAmpoule SHARED library.cpp library.h ParametrPack.h ParallelIterator.h WinstrolPointer.h Algo.h make_ducounter.h print_elements.h TypesPack.h MetanabolPointer.h Deleter.h Dementor.h Concepts.h Wrappers.h CompileTImeComputations.h DesignPatterns.h CheckingPointer.h UniversalThread.h SignalSystem.h)
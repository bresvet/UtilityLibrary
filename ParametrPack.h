//
// Created by Bartlomiej Swiatlon on 28.12.17.
//

#ifndef DAFFODIL_PARAMETRPACK_H
#define DAFFODIL_PARAMETRPACK_H

#include <type_traits>
#include <vector>
#include <algorithm>

namespace Daffodil
{
    template<template<typename E, typename All=std::allocator<E>> class C, typename...P, typename=std::is_same<E, P>::type>

    class ParametrPack : private C<E, All>
    {
    public:

        void add_back(P &&p)
        {
            C<E, All>::push_back(p);
        }

        void add_front(P &&p)
        {
            C<E, All>::push_front(p);
        }

        auto steal_element()
        {
            auto r = top();
            C<E, All>::pop_back();
            return r;
        }

        void clear()
        {
            while(!this->isEmpty())
            {
                C<E,All>::pop_back();
            }
        }

        int getParametrsQuantity()const
        {
            return C<E,All>::size();
        }

        explicit ParametrPack(const P &&...p)
        {
            this->push_back(p...);
        }

        auto top() const
        {
            return C<E, All>::end();
        }

        constexpr bool isEmpty() const
        {
            return C<E, All>::isEmpty();
        }

        template<typename...PC>
        ParametrPack(ParametrPack<PC...>const&par)
        {
            if (!par.isEmpty())
            {
                while (par.getParametrsQuantity() != this->getParametrsQuantity())
                {
                    par.add_back(opParametrPack.top());
                    this->add_front(par.steal_element());
                }
            }
        }


        template<typename...PC>
        ParametrPack(ParametrPack<E,C<E>,PC...>&&par)
        {
            while (!par.isEmpty())
            {
                this->add_front(opParametrPack.steal_element());
            }
        }


        template<typename...PC>
        ParametrPack&operator=(ParametrPack<E,C<E>,PC...>const&opParametrPack)
        {
            clear();

            if(this!=&opParametrPack) {

                while (opParametrPack.getParametrsQuantity() != this->getParametrsQuantity())
                {
                    opParametrPack.add_back(opParametrPack.top());
                    this->add_front(opParametrPack.steal_element());
                }
                return *this;
            }
        }

        template<typename...PC>
        ParametrPack&operator=(ParametrPack<E,C<E>,PC...>&&opParametrPack)
        {
            if (this != &opParametrPack)
            {
                while (!opParametrPack.isEmpty())
                {
                    this->add_front(opParametrPack.steal_element());
                }
            }
            else
            {
                opParametrPack.clear();
            }
            return *this;
        }

    /*    template<typename...PC>
        friend bool &operator==(ParametrPack<E,C<E>,PC...>&opPP)
        {
            std::unique(opPP.begin(),opPP.end(),[&](P&p,PC&pc)->bool{return std::is_same<decltype(p),decltype(pc)>::type;});
        }
*/
       };
}
#endif //DAFFODIL_PARAMETRPACK_H

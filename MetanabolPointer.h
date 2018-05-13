//
// Created by bs on 02.01.18.
//

#ifndef DAFFODIL_METANABOLPOINTER_H
#define DAFFODIL_METANABOLPOINTER_H

#include "WinstrolPointer.h"
#include "Algo.h"
#include <vector>
#include <memory>
#include <tuple>
#include <algorithm>
#include <type_traits>
#include "Deleter.h"
#include "CheckingPointer.h"


class WinstrolPointer;
class TypesPack;


template<typename...O>
class MetanabolPointer
{
public:

    explicit constexpr MetanabolPointer(const O&...o)noexcept
    {
     pointers.push_back(std::addressof(o));
    }

    MetanabolPointer(const MetanabolPointer&met)noexcept
          :pointers(met.pointers)
    {

    }

    MetanabolPointer(MetanabolPointer &&met)noexcept
         :pointers(std::move(met.pointers))
    {

    }

    MetanabolPointer&operator=(const MetanabolPointer &met)noexcept
    {
       pointers.clear();
        *this=met;
        return *this;
    }
    MetanabolPointer&operator=(const MetanabolPointer &&met)noexcept
    {
         pointers.clear();
        *this=std::move(met);
         return *this;
    }
    template<typename RT>
    struct InjectMetanabol<RT>
    {
        using singleObject=MetanabolPointer<RT>;
    };

    template<typename RT>
    struct InjectMetanabol<RT[]>
    {
        using array=MetanabolPointer<RT[]>;
    };

    template<typename RT,size_t s>
    struct InjectMetanabol<RT[s]>
    {
        struct invalidType{};
    };

    template<typename RT,typename...Arg>
    auto injectMetanabol(Arg&&...arg)->std::decay_t<typename InjectMetanabol<RT>::singleObject>
            {
             return MetanabolPointer<RT>(new RT(std::forward<Arg>(arg...)));
            }
    template<typename RT>
    auto injectMetanabol(size_t s)->std::decay_t<typename InjectMetanabol<RT>::array>
    {
        return MetanabolPointer<RT>(new std::remove_extent<RT>::type[s]);
    }

    template<typename RT,size_t s,typename...Arg>
    inline typename InjectMetanabol<RT[s]>::invalidType injectMetanabol(Arg&&...)=delete;

    template<typename P,
            typename=std::enable_if_t<std::is_same<P,O>::value||...> ,
            template<typename...W>class WC=TypesPack,
            template<typename...S> class SC=TypesPack,
            typename D=CrystalAmpoule::Deleter,
            typename T=TypesPack>
    explicit operator auto(const P &p,const WC &wc,const SC &sc)
    {
      CrystalAmpoule::execute_if(pointers.begin(),pointers.end(),
                             [&](O*vlp)mutable{delete vlp;},
                             [&](O*blp)->bool{std::is_same<O,P>::value && blp==&p;});
//        return WinstrolPointer<decltype(*(pointers.begin())),WC,SC>(*(pointers.begin()),wc,sc);
        return {*(pointers.begin()),wc,sc};
    }
  /*explicit operator std::unique_ptr()
    {

    }
    explicit operator std::shared_ptr()
    {

    }
    */
    //deprecated
    //explicit operator std::auto_ptr();


    ~MetanabolPointer() noexcept
    {
        std::for_each(pointers.begin(),pointers.end(),[&](O *lp){delete lp;});
    }

private:

    std::vector<O*>pointers;
   // std::vector<std::tuple<O*,unsigned>>pointersWithReferenceCnt;

    //template<typename List=TypesPack>
    //std::vector<std::tuple<typename List::Element,O*,unsigned,unsigned >


};
#endif //DAFFODIL_METANABOLPOINTER_H

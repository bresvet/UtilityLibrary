//
// Created by Bartlomiej Swiatlon on 28.12.17.
//

#ifndef DAFFODIL_WINSTROLPOINTER_H
#define DAFFODIL_WINSTROLPOINTER_H

#include <memory>
#include <any>
#include "TypesPack.h"
#include "Deleter.h"
#include "CheckingPointer.h"


class TypesPack;
class isEmpty;
class FrontT;
class popFrontT;
class pushFrontT;


namespace Daffodill
{

    template<typename P,
            typename=std::enable_if_t<std::is_object<P>::value>,
            template<typename...W>class WC=TypesPack,
            template<typename...S> class SC=TypesPack,
                    typename D=CrystalAmpoule::Deleter,
                            typename T=TypesPack>

//using EnableIfObject=std::enable_if_t<std::is_object<P>::value>;
//using WeakPack=ParametrPack<W...>;
//using StrongPack=ParametrPack<S...>;

    class WinstrolPointer final
    {
    public:

        constexpr WinstrolPointer()noexcept = default
        {
            pointer={};
            weakPack={};
            strongPack={};
            allRefCnt={};
            strongerRefCnt={};
            weakerRefCnt={};
            equalpowRefCnt={};
        }

        constexpr WinstrolPointer(const P &p,WC<W...>&&wcp,SC<S...>&&scp)noexcept
                     :weakPack(std::move(wcp)),strongPack(std::move(scp))
        {
            pointer=std::addressof(p);
            allRefCnt=0;
            strongerRefCnt=0;
            weakerRefCnt=0;
            equalpowRefCnt=0;
        }

        WinstrolPointer(WinstrolPointer const& win)noexcept
        {
            pointer=win.expired()?win.pointer:nullptr;
            addEqualpowRef();
        }

        WinstrolPointer(WinstrolPointer &&win)noexcept
                :pointer(std::move(win.pointer))
        {

        }

        WinstrolPointer&operator=(const WinstrolPointer &win)noexcept
        {
            this->pointer=win.pointer;
            return *this;
        }

        WinstrolPointer&operator=(WinstrolPointer &&win)noexcept
        {
            if(this!=&win)
            {
                this->pointer=win.pointer;
                win.pointer=nullptr;
            }

            return *this;
        }

        template<typename P2,
                typename=std::enable_if_t<std::is_object<P2>::value && (!std::is_same<P2,P>::value)>,
                template<typename...W2> class WC2=TypesPack,
                template<typename...S2> class SC2=TypesPack>

        WinstrolPointer(WinstrolPointer<P2,WC2,SC2>const&win)noexcept
        {
           this->weakPack=win.weakPack;
            this->strongPack=win.strongPack;
           this->allRefCnt=win.strongerRefCnt+1;
            this->strongerRefCnt=win.strongerRefCnt+1;
            this->equalpowRefCnt=win.equalpowRefCnt+1;
            this->weakerRefCnt=win.weakerRefCnt+1;
            pointer=win.pointer;
        }

        template<typename P2,
                typename=std::enable_if_t<std::is_object<P2>::value>,
                template<typename...W2> class WC2=TypesPack,
                template<typename...S2> class SC2=TypesPack>

        WinstrolPointer(WinstrolPointer<P2,WC2,SC2>&&win)noexcept
        {
            this->weakPack=std::move(win.weakPack);
            this->strongPack=std::move(win.strongPack);
            this->allRefCnt=win.allRefCnt;
            this->strongerRefCnt=win.strongerRefCnt;
            this->equalpowRefCnt=win.equalpowRefCnt;
            this->weakerRefCnt=win.weakerRefCnt;
            const_cast<CrystalAmpoule::CheckingPointer<P2>>(this->pointer);
        }

        /* template<typename P2,
                 typename=std::enable_if_t<std::is_object<P2>::value>,
                 template<typename...W2> class WC2=TypesPack,
                 template<typename...S2> class SC2=TypesPack>


         WinstrolPointer&operator=(const std::shared_ptr<P2>&sha)noexcept
         {

         }
         */




        template<typename P2,
                typename=std::enable_if_t<std::is_object<P2>::value>,
                template<typename...W2> class WC2=TypesPack,
                template<typename...S2> class SC2=TypesPack>


        WinstrolPointer&operator=(const WinstrolPointer<P2,WC2,SC2>&win)
        {
            this->weakPack=win.weakPack;
            this->strongPack=win.strongPack;
            this->allRefCnt=win.strongerRefCnt+1;
            this->strongerRefCnt=win.strongerRefCnt+1;
            this->equalpowRefCnt=win.equalpowRefCnt+1;
            this->weakerRefCnt=win.weakerRefCnt+1;
            const_cast<CrystalAmpoule::CheckingPointer<P2>>(this->pointer);
            return *this;
        }


        template<typename P2,
                typename=std::enable_if_t<std::is_object<P2>::value>,
                template<typename...W2> class WC2=TypesPack,
                template<typename...S2> class SC2=TypesPack>

        WinstrolPointer&operator=(WinstrolPointer<P2,WC2,SC2>&&win)
        {
            this->weakPack=std::move(win.weakPack);
            this->strongPack=std::move(win.strongPack);
            this->allRefCnt=win.allRefCnt;
            this->strongerRefCnt=win.strongerRefCnt;
            this->equalpowRefCnt=win.equalpowRefCnt;
            this->weakerRefCnt=win.weakerRefCnt;
            const_cast<CrystalAmpoule::CheckingPointer<P2>>(this->pointer);
            return *this;
        }

 template<typename O>
 WinstrolPointer &operator=(WinstrolPointer<O,WC,SC> const &win)
        {
            this->allRefCnt=win.strongerRefCnt+1;
            this->strongerRefCnt=win.strongerRefCnt+1;
            this->equalpowRefCnt=win.equalpowRefCnt+1;
            this->weakerRefCnt=win.weakerRefCnt+1;
            const_cast<CrystalAmpoule::CheckingPointer<O>>(this->pointer);
            return *this;
        }
template<typename O>
        WinstrolPointer &operator=(WinstrolPointer &&win)
        {
            this->allRefCnt=win.allRefCnt;
            this->strongerRefCnt=win.strongerRefCnt;
            this->equalpowRefCnt=win.equalpowRefCnt;
            this->weakerRefCnt=win.weakerRefCnt;
            const_cast<CrystalAmpoule::CheckingPointer<O>>(this->pointer);
            return *this;
        }


        constexpr bool operator==(WinstrolPointer<P, WC<W...>, SC<S...>>&opWP)
 {
return(this->get().get()==opWP.get().get() && this->weakPack==opWP.weakPack && this->strongPack==opWP.strongPack);
 }

        constexpr bool operator!=(WinstrolPointer<P,WC<W...>,SC<S...>>&opWP)
        {
            return(this->get().get()!=opWP.get().get() || this->weakPack!=opWP.weakPack || this->strongPack!=opWP.strongPack);
        }



        auto getDeleter(WinstrolPointer &win)noexcept
        {
            return typename D::getDeleter();
        }

        constexpr bool expired() const
        {
            return std::is_null_pointer<pointer>::value;
        }

        template<typename RT>
        class InjectWinstrol
        {
        public:
            using singleObject=WinstrolPointer<RT>;
        };

        template<typename RT>
        class InjectWinstrol<RT[]>
        {
        public:
            using array=WinstrolPointer<RT[]>;
        };

        template<typename RT,size_t Bound>
        class InjectWinstrol<RT[Bound]>
        {
        public:
           struct invalid_t{};
        };


        template<typename RT,typename...Arg>

        auto injectWinstrol(Arg&&...arg)->std::decay_t<typename InjectWinstrol<RT>::singleObject>
        {
            return WinstrolPointer<RT>(new RT(std::forward<Arg>(arg...)));
        }

        template<typename RT>
        auto injectWinstrol(size_t s)->std::decay_t<typename InjectWinstrol<RT>::array>
        {
            return WinstrolPointer<RT>(new std::remove_extent<RT>::type[s]);
        }

template<typename RT,typename...Arg>
        inline typename InjectWinstrol<RT>::invalid_t injectWinstrol(Arg&&...)=delete;

        template<template<typename...SW>class SWC,template<typename...SS>class SSC>
        void resetOnlyPacks(const SWC<SW...>&swcp,const SSC<SS...>&sscp)
        {
            this->weakPack=swcp;
            this->strongPack=sscp;
        }




        template<typename S>
        void swapOnlyObject(const S &s)
        {
            const_cast<CrystalAmpoule::CheckingPointer<S>>(pointer);
        }

        template<typename S, template<typename...SW> class SWC,
                template<typename...SS> class SSC>
        void swapObjectAndPacks(const S &s, const SWC<SW...> &swcp, const SSC<SS...> &sscp)
        {
            this->weakPack=swcp;
            this->strongPack=sscp;
            const_cast<CrystalAmpoule::CheckingPointer<S>>(pointer);
        }

        void addWeakerRef()
        {
            weakerRefCnt++;
            allRefCnt++;
        }

        void addStrongerRef()
        {
            strongerRefCnt++;
            allRefCnt++;
        }

        void addEqualpowRef()
        {
            equalpowRefCnt++;
            allRefCnt++;
        }


        int getWeakerRefCnt() const
        {
            return weakerRefCnt;
        }

        int getStrongerRefCnt() const
        {
            return strongerRefCnt;
        }

        int getAllRefCnt() const
        {
            return allRefCnt;
        }

        int getEqualpowRefCnt()const
        {
            return equalpowRefCnt;
        }

        CrystalAmpoule::CheckingPointer<P> get()const
        {
            return pointer;
        }

        std::shared_ptr lockShared()
        {
            return static_cast<std::shared_ptr>(*this);
        }

        std::weak_ptr lockWeak()
        {
            return static_cast<std::weak_ptr>(*this);
        }

        template<typename O>
        bool ownerBefore(const std::shared_ptr<O>&osptr)
        {
            return(if constexpr this->get()==osptr.get());
        }

        template<typename O>
        bool ownerBefore(const WinstrolPointer<O>&owinptr)
        {
            return(if constexpr this->get()==owinptr.get().get());
        }

        T& operator *()
        {
            return *pointer;
        }

        T* operator ->()
        {
            return pointer->;
        }


       /* explicit operator std::weak_ptr()
        {
            while(!isEmpty<*weakPack>)
            {
                pushFrontT<*strongPack>(FrontT<*weakPack>);
                popFrontT<*weakPack>;
            }
        }

        explicit operator std::shared_ptr()
        {
            while(!isEmpty<strongPack>)
            {
                pushFrontT<*weakPack>(FrontT<*strongPack>);
                popFrontT<*strongPack>;
            }

        }
*/

    private:

        uint weakerRefCnt;
        int strongerRefCnt;
        int equalpowRefCnt;
        int allRefCnt;
        CrystalAmpoule::CheckingPointer<P>pointer;

    public:


    private:
        TypesPack *weakPack;
        TypesPack *strongPack;
        std::vector<std::pair<std::any,unsigned>>objectsWithRefCnt;

    };




}

#endif //DAFFODIL_WINSTROLPOINTER_H

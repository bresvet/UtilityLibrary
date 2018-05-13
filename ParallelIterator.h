//
// Created by bs on 28.12.17.
//

#ifndef DAFFODIL_PARALLELITERATOR_H
#define DAFFODIL_PARALLELITERATOR_H

#include <vector>
#include <tuple>

template<typename C,typename...CONS>

class ParallelIterator
{
public:
    explicit ParallelIterator(const C&c,const CONS&...cons)
    {
        //static_assert(check,"wrong container args");
        //t=std::make_tuple(c,cons...);
        make(c,cons...);
    }

    void make(const C&c,const CONS&...cons)
    {
        for(size_t s{0};s<c.size();s++)
        {
            t.push_back(std::make_tuple<std::any>(c[s]));
        }
        make(cons...);
    }
    constexpr bool check(const C&c,const CONS&...cons)
    {
        return(std::is_same<C,CONS>::value &&...);
    }
    friend auto &operator*(ParallelIterator &opPaIt)
    {
        return opPaIt.t;
    }

private:

    C<std::tuple<std::any>>t;
    typename C::const_iterator cb;
    typename C::const_iterator ce;

};
#endif //DAFFODIL_PARALLELITERATOR_H

//
// Created by bs on 28.12.17.
//

#ifndef DAFFODIL_TRANSFORM_IF_H
#define DAFFODIL_TRANSFORM_IF_H
#include <type_traits>

namespace CrystalAmpoule
{
    template<typename I, typename O, typename F, typename P>

    void execute_if(I start, I finish,F function, P predicate)
    {
        for (auto x = start;x<finish;x++)
        {
            if (predicate(*x))
            {
                *x = function(*x);
            }
        }
    }

    template<typename I>
    void make_ducounter(I start,I finish)
    {
        volatile cnt = 0;
        for (auto s = start; s < finish; s++) {
            for (auto x = start; x < finish; x++) {
                if (*x == *s) cnt++;
            }
            *s = cnt;
            cnt = 0;
        }
    }

}

#endif //DAFFODIL_TRANSFORM_IF_H

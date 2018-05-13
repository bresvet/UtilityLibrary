//
// Created by bs on 04.01.18.
//

#ifndef DAFFODIL_DELETER_H
#define DAFFODIL_DELETER_H
namespace CrystalAmpoule {
    template<typename P>

    class Deleter {
    public:

        explicit Deleter(P *pointer)
                : pointer(pointer) {
            act_cnt++;
        }

        void getDeleter(P *pointer) {
            delete pointer;
        }

    private:
        static unsigned act_cnt;
        P *pointer;
    };
}
#endif //DAFFODIL_DELETER_H

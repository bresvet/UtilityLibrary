//
// Created by bs on 29.01.18.
//

#ifndef CRYSTALAMPOULE_CHECKINGPOINTER_H
#define CRYSTALAMPOULE_CHECKINGPOINTER_H

#include <type_traits>

namespace CrystalAmpoule {
    template<typename T>
    class CheckingPointer {
    public:

        T &operator*() const {
            return *pointer;
        }

        T *operator->() const {
            return pointer;
        }

        T *get() const {
            return pointer;
        }

        ~CheckingPointer() {
            delete pointer;
        }

        void operator=(T *op)
        {
            if (op==nullptr) delete this;
            this->pointer
        }

        template<typename O,typename=std::enable_if<!std::is_same<T,O>::type>>
        void operator=(O *op) {
            this->pointer = op;
        }

    private:

        T *pointer;
    };
}
#endif //CRYSTALAMPOULE_CHECKINGPOINTER_H

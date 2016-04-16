#ifndef CREATE_TYPES_HPP
#define CREATE_TYPES_HPP

#include "../types.hpp"
#include "create.hpp"

namespace details
{
    struct forbid_creation_on_heap
    {
    private:
        void* operator new(size_t) = delete;          // standard new
        void* operator new(size_t, void*) = delete;   // placement new
        void* operator new[](size_t) = delete;        // array new
        void* operator new[](size_t, void*) = delete; // placement array new
    };

}//end namespace details


#endif //CREATE_TYPES_HPP

#ifndef CREATE_TYPES_HPP
#define CREATE_TYPES_HPP

namespace Flexy
{ 
    struct forbid_creation_on_heap
    {
    private:
        void* operator new(size_t) = delete;          // standard new
        void* operator new(size_t, void*) = delete;   // placement new
        void* operator new[](size_t) = delete;        // array new
        void* operator new[](size_t, void*) = delete; // placement array new
    };

}//end namespace Flexy


#endif //CREATE_TYPES_HPP

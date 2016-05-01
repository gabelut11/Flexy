/* 
 * File:   creaion_policy2.h
 * Author: gabi
 *
 * Created on May 1, 2016, 11:14 AM
 */

#ifndef CREAION_POLICY2_H
#define	CREAION_POLICY2_H

#include <tuple>
#include <type_traits>

namespace util
{
    
enum class creation_type  : unsigned int
{
    on_heap, in_place, smart_ptr
};
        
template< creation_type c, template<class...> class... SmartPtr>
struct creation_policy;

template<>
struct creation_policy<creation_type::on_heap>
{  
    template<class ReturnType, class... Args>
    static ReturnType* create(Args&&... args)
    {
        //typedef void* (&Allocator)(size_t) = operator new; 
        //void *ptr = Allocator(sizeof(ReturnType));
        void *ptr = operator new(sizeof(ReturnType));
        new(ptr) ReturnType(std::forward<Args>(args)...);
        return (ReturnType*)ptr;
    }
};

template<>
struct creation_policy<creation_type::in_place>
{
    template<class ReturnType, class... Args>
    static ReturnType* create(void *& ptr, Args&&... args)
    {
        new(ptr) ReturnType(std::forward<Args>(args)...);
        return (ReturnType*)ptr;
    }

    template<class ReturnType, class... Args>
    static ReturnType* create(ReturnType *& ptr, Args&&... args)
    {
        new(ptr) ReturnType(std::forward<Args>(args)...);
        return ReturnType((ReturnType*)ptr);
    }
};

template<template<class...> class SmartPtrType>
struct creation_policy< creation_type::smart_ptr, SmartPtrType>
{
    template<class ReturnType, class... Args>
    static SmartPtrType<ReturnType> create(Args&&... args)
    {  
        return SmartPtrType<ReturnType>( new ReturnType( std::forward<Args>(args)... ) );
    }
};

template< class Allocator>
void* allocate2(size_t n)
{
    static Allocator allocator;
    return allocator.allocate(n);
}


}//namespace util


#endif	/* CREAION_POLICY2_H */


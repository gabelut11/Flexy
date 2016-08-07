/*
 * File:   creaion_policy2.h
 * Author: gabi
 *
 * Created on May 1, 2016, 11:14 AM
 */

#ifndef CREAION_POLICY_H
#define	CREAION_POLICY_H

#include <tuple>
#include <type_traits>
#include "options.hpp"

namespace Flexy
{
    namespace generate
    {

    template< creation c, template<class...> class...>
    struct creation_policy;

    template<>
    struct creation_policy<creation::on_heap>
    {
        template<class T>
        struct get_return_type
        {
            typedef T* type;
        };

        template<class ReturnType, class... Args>
        static ReturnType* create(Args&&... args)
        {
            void *ptr = operator new(sizeof(ReturnType));
            new(ptr) ReturnType(std::forward<Args>(args)...);
            return (ReturnType*)ptr;
        }
    };

    template<>
    struct creation_policy<creation::in_place>
    {
        template<class T>
        struct get_return_type
        {
            typedef T* type;
        };

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
    struct creation_policy< creation::smart_ptr, SmartPtrType>
    {
        template<class T>
        struct get_return_type
        {
            typedef SmartPtrType<T> type;
        };

        template<class ReturnType, class... Args>
        static SmartPtrType<ReturnType> create(Args&&... args)
        {
            return SmartPtrType<ReturnType>( new ReturnType( std::forward<Args>(args)... ) );
        }
    };

    }//end namespace factory

}//end namespace Flexy


#endif	/* CREAION_POLICY_H */


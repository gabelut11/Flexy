#ifndef GENERATE_INTERFACE_HPP
#define GENERATE_INTERFACE_HPP

#include <tuple>
#include "details/hierachy/base.hpp"
#include "details/hierachy/subobject_impl.hpp"

namespace Flexy
{

    namespace generate
    {

    template<template<class...> class Tuple, class First, class... Args >
    struct generate_hierachy:   public details::left_base< Tuple< First, Args...> >::type,
                                public details::right_base< Tuple< First, Args...> >::type
    {
    };

    //-----------------------------------------------------------------------------------------

    template<size_t index, class Hierarchy>
    struct subobject
    {
        typedef typename details::subobject_impl<index, Hierarchy>::type type;
    };

    //-----------------------------------------------------------------------------------------

    template<size_t index, class... Args, template<class...> class H>
    typename subobject<index, H<Args...>>::type const &get_subobject(const H<Args...> &h)
    {
        typedef typename subobject<index, H<Args...> >::type ReturnType_t;
        const ReturnType_t& result = h;
        return result;
    }

    template<size_t index, class... Args, template<class...> class H>
    typename subobject<index, H<Args...>>::type &get_subobject(H<Args...> &h)
    {
        typedef typename subobject<index, H<Args...> >::type ReturnType_t;
        ReturnType_t& result = h;
        return result;
    }

    }//end namespace generate

}//end namespace Flexy

#endif

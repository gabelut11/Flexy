/*
 * File:   get_creation_policy.hpp
 * Author: gabi
 *
 * Created on May 7, 2016, 4:30 PM
 */

#ifndef GET_CREATION_POLICY_HPP
#define	GET_CREATION_POLICY_HPP

#include "creation_policy.h"

namespace Flexy
{
    namespace generate
    {

    template<class...> struct PlaceHolder
    {};

    template< creation c, template<class...> class...>
    struct get_creation_policy;

    template< creation c>
    struct get_creation_policy<c>
    {
        typedef creation_policy<c> type;
    };

    template< creation c, template<class...> class SmartPtr>
    struct get_creation_policy<c, SmartPtr>
    {
        typedef creation_policy<c, SmartPtr> type;
    };

    template< creation c>
    struct get_creation_policy<c, PlaceHolder>
    {
        typedef creation_policy<c> type;
    };

    } //end namespace generate

}//end namespace Flexy

#endif	/* GET_CREATION_POLICY_HPP */


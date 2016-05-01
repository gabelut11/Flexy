/* 
 * File:   factory_utilities.hpp
 * Author: gabi
 *
 * Created on May 1, 2016, 1:47 PM
 */

#ifndef FACTORY_UTILITIES_HPP
#define	FACTORY_UTILITIES_HPP

#include "generate_hierarchy.hpp"
#include "creation_policy2.h"
#include <type_traits>

namespace util
{
    
template<util::creation_type type, class... PolicyArgs>
struct create
{
    template<class...>
    struct types;
    
    template<class First, class... Rest> 
    struct types<First, Rest...> : public util::generate_hierachy< types, First, Rest...> 
    {
        typedef std::tuple<First, Rest...>  types_t;
        typedef types<First, Rest...>       factory_type_t;
    
        template<class T, class... Args>
        static T * create(Args&&... args)
        {
            static const size_t index = util::find_index<T, types_t>::value;
            static_assert(index >=0, "invalid type");

            typedef typename util::subobject<index, factory_type_t>::type subobject_t;
            return subobject_t::create(std::forward<Args>(args)...);
        }
        
    };
    
    template<class Last>
    struct types<Last>
    {
        template<class... Args>
        static Last * create(Args&&... args)
        {
            const static util::creation_type ct = type;
            typedef typename util::creation_policy<ct, PolicyArgs...> creator_t;
            return creator_t:: template create<Last>(std::forward<Args>(args)...);
        }
    };
};


    
}//end namespace util

#endif	/* FACTORY_UTILITIES_HPP */


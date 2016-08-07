/*
 * File:   generate-factory.hpp
 * Author: gabi
 *
 * Created on May 1, 2016, 1:47 PM
 */

#ifndef GENERATE_FACTORY_HPP
#define	GENERATE_FACTORY_HPP

#include "details/creation/get_creation_policy.hpp"
#include "generate_hierarchy.hpp"
#include <type_traits>

namespace Flexy
{
    namespace generate
    {

    template<creation type, template<class...> class... SmartPtr>
    struct factory
    {
        typedef typename get_creation_policy<type, SmartPtr...>::type creator_t;

        template<class...>
        struct for_types;

        template<class First, class... Rest>
        struct for_types<First, Rest...> : public generate_hierachy< for_types, First, Rest...>
        {
            typedef std::tuple<First, Rest...>  types_t;
            typedef for_types<First, Rest...>   factory_type_t;

            template<class T, class... Args>
            typename creator_t:: template get_return_type<T>::type create(Args&&... args)
            {
                static const size_t index = util::find_index<T, types_t>::value;
                static_assert(index >=0, "invalid type");

                auto& subobj = get_subobject<index>(*this);
                return subobj.create(std::forward<Args>(args)...);
            }

        };

        template<class Last>
        struct for_types<Last>
        {
            typedef typename creator_t:: template get_return_type<Last>::type return_type_t;

            template<class... Args>
            return_type_t create(Args&&... args)
            {
                return creator_t:: template create<Last>(std::forward<Args>(args)...);
            }
        };
    };

    }//end namespace generate

}//end namespace Flexy

#endif	/* GENERATE_FACTORY_HPP */


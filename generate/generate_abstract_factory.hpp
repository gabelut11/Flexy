/*
 * File:   generate_abstract_factory.hpp
 * Author: gabi
 *
 * Created on May 8, 2016, 6:23 PM
 */

#ifndef GENERATE_ABSTRACT_FACTORY_HPP
#define	GENERATE_ABSTRACT_FACTORY_HPP

#include "details/creation/get_creation_policy.hpp"
#include "generate_hierarchy.hpp"
#include "details/creation/creation_policy.h"
#include <type_traits>
#include <iostream>

namespace Flexy
{
    namespace generate
    {

    template<creation type, template<class...> class... SmartPtr>
    struct abstract_factory
    {
        template<class...>
        struct of;

        template<class First, class... Rest>
        struct of<First, Rest...>
        {
            typedef std::tuple<First, Rest...> abstract_products_t;
            typedef typename get_creation_policy<type, SmartPtr...>::type creation_policy_t;

            template<class FirstConcrete, class... RestConcrete>
            struct that_creates : generate_hierachy<that_creates, FirstConcrete, RestConcrete...>
            {
                private:
                typedef std::tuple<FirstConcrete, RestConcrete...> concrete_products_t;

                public:
                    template<class T, class... Args>
                    typename creation_policy_t::template get_return_type<T>::type
                    create(Args&&... args)
                    {
                        constexpr int index = util::find_index<T, abstract_products_t>::value;
                        auto& subobj = get_subobject<index>(*this);
                        return subobj.create(std::forward<Args>(args)...);
                    }
            };

            template<class Last>
            struct that_creates<Last>
            {
                template<class... Args>
                typename creation_policy_t::template get_return_type<Last>::type
                create(Args&&... args)
                {
                    return creation_policy_t:: template create<Last>(std::forward<Args>(args)...);
                }
            };
        };
    };

    }//end namespace generate

}//end namespace Flexy

#endif	/* GENERATE_ABSTRACT_FACTORY_HPP */


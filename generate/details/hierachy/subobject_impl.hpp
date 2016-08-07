/* 
 * File:   subobject.hpp
 * Author: gabi
 *
 * Created on May 7, 2016, 5:54 PM
 */

#ifndef SUBOBJECT_HPP
#define	SUBOBJECT_HPP

#include "base.hpp"
#include "../../../util/types_utilities.hpp"

namespace Flexy
{
    namespace generate
    {
        namespace details
        {

        template<size_t index, class...>
        struct subobject_impl;

        template<size_t index, class... Args, template<class...> class Hierarchy>
        struct subobject_impl<index, Hierarchy<Args...> >
        {
            static_assert(sizeof...(Args) > 0, "invalid type list");
            static_assert(index < sizeof...(Args), "invalid index value");

            typedef typename left_base<Hierarchy<Args...>>::type left_base_t;
            typedef typename right_base<Hierarchy<Args...>>::type right_base_t;

            static const size_t num_iterations = sizeof...(Args) - index;
            typedef subobject_impl<index, left_base_t> next_t;
            typedef typename std::conditional<(num_iterations == 1), util::identity<right_base_t>, next_t>::type result_t;

        public:
            typedef typename result_t::type type;
        };

        }//end namespace details

    }//end namespace generate

}//end namespace Flexy

#endif	/* SUBOBJECT_HPP */


/*
 * File:   creation_type.hpp
 * Author: gabi
 *
 * Created on May 2, 2016, 11:41 AM
 */

#ifndef OPTIONS_HPP
#define	OPTIONS_HPP

namespace Flexy
{
    enum class creation  : unsigned int
    {
        on_heap, in_place, smart_ptr
    };

}//end namespace Flexy


#endif	/* OPTIONS_HPP */


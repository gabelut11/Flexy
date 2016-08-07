/*
 * File:   concrete_factory.h
 * Author: gabi
 *
 * Created on April 24, 2016, 11:45 AM
 */

#ifndef CONCRETE_FACTORY_H
#define	CONCRETE_FACTORY_H

#include "generate/generate_factory.hpp"
#include "generate/details/creation/options.hpp"
#include <tuple>

namespace Flexy
{

template<creation c1, template<class...> class SmartPtr = generate::PlaceHolder>
struct generate_factory
{
    template<class... Args>
    struct that_creates
    {
        typedef typename generate::factory<c1, SmartPtr>:: template for_types<Args...> type;
    };
};

}//end namespace Flexy



#endif	/* CONCRETE_FACTORY_H */


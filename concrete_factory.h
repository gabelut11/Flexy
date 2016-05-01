/* 
 * File:   concrete_factory.h
 * Author: gabi
 *
 * Created on April 24, 2016, 11:45 AM
 */

#ifndef CONCRETE_FACTORY_H
#define	CONCRETE_FACTORY_H

#include "util/generate_hierarchy.hpp"
#include "util/creation_policy.hpp"
#include "util/factory_utilities.hpp"
#include <tuple>

namespace Flexy
{
    
template<util::creation_type c1>
struct factory
{
    template<class... Args>
    struct create
    {
        typedef typename util::create<c1>:: template types<Args...> type;
    };
};

}//end namespace Flexy



#endif	/* CONCRETE_FACTORY_H */


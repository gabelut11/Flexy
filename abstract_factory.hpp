/*
 * File:   abstract_factory2.hpp
 * Author: gabi
 *
 * Created on May 8, 2016, 6:18 PM
 */

#ifndef ABSTRACT_FACTORY2_HPP
#define	ABSTRACT_FACTORY2_HPP

#include "generate/generate_factory.hpp"
#include "generate/details/creation/options.hpp"
#include "generate/generate_abstract_factory.hpp"
#include <tuple>

namespace Flexy
{

template<creation c1, template<class...> class SmartPtr = generate::PlaceHolder>
struct generate_abstract_factory
{
    template<class... AbstractTypes>
    struct of
    {
        template<class... ConcreteTypes>
        struct that_creates
        {
            private:
                typedef typename generate::abstract_factory<c1, SmartPtr>:: template of<AbstractTypes...> abstract_factory_t;

            public:
                typedef typename abstract_factory_t:: template that_creates<ConcreteTypes...> type;
        };
    };
};

}//end namespace Flexy

#endif	/* ABSTRACT_FACTORY2_HPP */


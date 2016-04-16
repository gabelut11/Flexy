#ifndef GENERATE_FUNCTOR_HPP
#define GENERATE_FUNCTOR_HPP

#include <utility>

namespace util
{

    template<class...>
    struct generate_functor;

    template<class Ret, class... Args, class Implementation>
    struct generate_functor< Ret(Args...), Implementation>
    {
        Ret operator()(Args... args)
        {
            return impl(std::forward<Args>(args)...);
        }
        
    private:
        Implementation impl;
    };


}//end namespace util

#endif

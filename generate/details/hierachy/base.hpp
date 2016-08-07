#ifndef HIERARCHY_HPP
#define HIERARCHY_HPP

#include "../../../util/types_utilities.hpp"

namespace Flexy
{
    namespace generate
    {
        namespace details
        {

        template<class...>
        struct left_base;

        template< template<class...> class Tuple, class First, class... Args>
        struct left_base< Tuple<First, Args...> >
        {
            typedef typename util::transfer_first_n < sizeof...(Args), Tuple,  First, Args...>::type type;
        };

        template< template<class...> class Tuple, class Last>
        struct left_base< Tuple<Last> >
        {
            typedef Tuple<Last> type;
        };

        //-----------------------------------------------------------------------------------------

        template<class...>
        struct right_base;

        template< template<class...> class Tuple, class First, class... Args>
        struct right_base< Tuple<First, Args...> >
        {
            typedef typename util::transfer_last_n< 1, Tuple, First, Args...>::type type;
        };

        template< template<class...> class Tuple, class Last>
        struct right_base< Tuple<Last> >
        {
            typedef Tuple<Last> type;
        };

        }//end namespace details

    }//end namespace generate

}//end namespace Flexy



#endif

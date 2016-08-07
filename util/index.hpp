#ifndef TYPES_H
#define TYPES_H


namespace util
{
    template<size_t... vals>
    struct index
    {
    };
    
    namespace details
    {
        template<size_t n, size_t... args>
        struct make_index_impl
        {
            typedef typename make_index_impl<n-1, n, args...>::type type;
        };

        template< size_t... args>
        struct make_index_impl<0, args...>
        {
            typedef index< 0, args...> type;
        };
        
    }//end namespace details

    //------------------------------------------------------------------------------------------------------



}//end namespace util


#endif

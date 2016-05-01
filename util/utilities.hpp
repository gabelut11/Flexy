#ifndef UTIL_HPP
#define UTIL_HPP

#include <type_traits>
#include "types.hpp"
#include "details/create.hpp"
#include "details/utilities_impl.hpp"

namespace util
{
    
template<class T>
struct identity
{
    typedef typename details::identity_impl<T>::type type;
};

//------------------------------------------------------------------------------------------------------

template<class... Args>
struct add;

template<class... Args1, class... Args2, template<class...> class Tuple>
struct add< Tuple<Args1...>, Tuple<Args2...> >
{
    typedef Tuple<Args1..., Args2...> type;
};

template<class... Args1, class... Args2, template<class...> class Tuple>
struct add < Tuple<Args1...>, Args2...>
{
    typedef Tuple<Args1..., Args2...> type;
};

//------------------------------------------------------------------------------------------------------

template<size_t n, class T>
struct get_first_n;

template<size_t n, class... Args, template<class...> class Tuple>
struct get_first_n<n, Tuple<Args...> >
{
    typedef typename details::get_first_n_impl<n, Tuple<Args...>>::type type;
};

//------------------------------------------------------------------------------------------------------

template<size_t n, class... Args>
struct erase_first_n;

template<size_t n, class... Args, template<class...> class Tuple >
struct erase_first_n<n, Tuple<Args...> >
{
    private:
    static const size_t size =  sizeof...(Args);
    typedef details::erase_first_n_impl< n, Tuple<Args...>> impl_t;

    public:
    typedef typename std::conditional<(n >= size), Tuple<>, typename impl_t::type>::type type;
};

//------------------------------------------------------------------------------------------------------

template<size_t n, class... Args>
struct erase_last_n;

template<size_t n, class... Args, template<class...> class Tuple>
struct erase_last_n<n, Tuple<Args...> >
{
    public:
    typedef typename details::erase_last_n_impl<n, Tuple<Args...>>::type type;

};

//------------------------------------------------------------------------------------------------------

template < size_t n, class... T>
struct get_last_n;

template<size_t n, class... Args, template<class...> class Tuple>
struct get_last_n<n, Tuple<Args...>>
{
    typedef typename details::get_last_n_impl<n, Tuple<Args...> >::type type;
};

//------------------------------------------------------------------------------------------------------

template < size_t index, size_t n, class... T>
struct get_n;

template<size_t index, size_t n, template<class...> class Tuple>
struct get_n<index, n, Tuple<> >
{
    typedef Tuple<> type;
};

template< size_t index, size_t n, class... Args, template<class...> class Tuple>
struct get_n<index, n, Tuple<Args...>>
{
    private:
    const static size_t size = sizeof...(Args);
    const static size_t valid_index = (index>size) ? size:index;
    const static size_t valid_n = ( (n + valid_index) > size) ? (size - valid_index) : n;
    typedef erase_first_n<valid_index, Tuple<Args...>> move_to_index_t;

    public:
    typedef typename get_first_n<valid_n, typename move_to_index_t::type >::type type;
};  

//------------------------------------------------------------------------------------------------------

template<size_t min, size_t max, class Tuple>
struct get_range;

template<size_t min, size_t max, class First, class... Args, template<class...> class Tuple> //[min, max)
struct get_range< min, max, Tuple<First, Args...> >
{
    private:
    const static size_t size = sizeof...(Args) + 1;
    const static size_t stop = (max > size) ? size : max;
    const static size_t start = (min > stop) ? stop : min;
    typedef details::get_range_impl< start, stop, Tuple<First, Args...> > impl_t;

    public:
    typedef typename std::conditional< (start == stop), Tuple<>, typename impl_t::type>::type type;

};

//------------------------------------------------------------------------------------------------------

template<size_t index, size_t n, class... T>
struct erase_n;

template<size_t index, size_t n, template<class...> class Tuple>
struct erase_n<index, n, Tuple<>>
{
    typedef Tuple<> type;
};

template<size_t index, size_t n, class... Args, template<class...> class Tuple>
struct erase_n<index, n, Tuple<Args...>>
{
    private:
    const static size_t size = sizeof...(Args);
    const static bool is_index_valid = (index<size);
    const static size_t valid_n =  (!is_index_valid) ? 0 : (index + n > size) ? size - index : n;
    const static bool empty = (!is_index_valid) || (valid_n == size);

    typedef Tuple<Args...> tuple_t;
    typedef get_range<0, index, tuple_t> range1_t;
    typedef get_range<index + valid_n, size, tuple_t> range2_t;
    typedef add<typename range1_t::type, typename range2_t::type> result_t;

    public:
    typedef typename std::conditional< empty, Tuple<>, typename result_t::type>::type type;
};

//------------------------------------------------------------------------------------------------------

template< template<class...> class To, class... T >
struct transfer_all
{
    typedef typename details::transfer_all_impl< To, T... >::type type;
};

template <  template<class...> class To,  template<class...> class From, class... T>
struct transfer_all< To, From<T...> >
{
    typedef typename details::transfer_all_impl<To, From<T...> > type;
};

//------------------------------------------------------------------------------------------------------

template< size_t n, template<class...> class To, class... Args >
struct transfer_first_n
{
    typedef typename details::transfer_first_n_impl<n, To, Args...>::type type;
};

template < size_t n, template<class...> class To,  template<class...> class From, class... T >
struct transfer_first_n< n, To,  From<T...> >
{
    typedef typename details::transfer_first_n_impl<n, To, From<T...> >::type type;
};

//------------------------------------------------------------------------------------------------------

template< size_t n, template<class...> class To, class... Args >
struct transfer_last_n
{
    private:
    typedef std::tuple<Args...> tuple_t;
    typedef typename get_last_n< n, tuple_t>::type source_t;

    public:
    typedef typename transfer_all< To, source_t>::type type;
};

//------------------------------------------------------------------------------------------------------

template< size_t index, size_t n, template<class...> class To, class... Args >
struct transfer_n
{
    private:
    typedef std::tuple<Args...> tuple_t;
    typedef typename get_n<index, n, tuple_t>::type source_t;

    public:
    typedef typename transfer_all< To, source_t >::type type;
};

template< size_t index, size_t n, template<class...> class To, class... Args, template<class...> class From >
struct transfer_n< index, n, To, From<Args...> >
{
    private:
    typedef typename get_n<index, n, From<Args...> >::type source_t;

    public:
    typedef typename transfer_all< To, source_t >::type type;
};   

//-------------------------------------------------------------------------------------------------------

template<size_t n>
struct make_index
{
    typedef typename details::make_index_impl<n>::type type;
};

//-------------------------------------------------------------------------------------------------------

template<template<class> class Fun, class... Args>
struct transform
{
    typedef typename details::transform_impl< std::tuple<Args...>, Fun>::type type;
};

template<template<class> class Fun, class... Args>
struct transform< Fun, std::tuple<Args...>>
{
    typedef typename details::transform_impl< std::tuple<Args...>, Fun>::type type;  //TODO: replace tuple
};

//-------------------------------------------------------------------------------------------------------

template< class T, class... Args>
struct find_index
{
    static const int value = details::find_index_impl< sizeof...(Args), T, std::tuple<Args...>>::value;
};

template< class T, template<class...> class Tuple, class... Args>
struct find_index<T, Tuple<Args...>>
{
    static const int value = details::find_index_impl< sizeof...(Args), T, Tuple<Args...>>::value;
};

//-------------------------------------------------------------------------------------------------------

template< class T, class... Args>
struct contains
{
    static const bool value = (find_index<T, Args...>::value >= 0);
};

//-------------------------------------------------------------------------------------------------------

template<size_t index, class... Args>
struct find_type
{
    private:
    static_assert(sizeof...(Args) > 0, "empty type list" );
    static_assert(index < sizeof...(Args), "invalid index value" );

    const static bool not_empty = (sizeof...(Args) >0);
    typedef std::enable_if<not_empty, std::tuple<Args...>> get_tuple_if_valid_t;

    public:
    typedef typename details::find_type_impl< index, typename get_tuple_if_valid_t::type >::type type;
};

//-------------------------------------------------------------------------------------------------------

template<size_t index, template<class...> class Tuple, class... Args>
struct find_type<index, Tuple<Args...>>
{
    private:
    static_assert(sizeof...(Args) > 0, "empty type list" );
    static_assert(index < sizeof...(Args), "invalid index value" );

    const static bool not_empty = (sizeof...(Args) >0);
    typedef std::enable_if<not_empty, Tuple<Args...>>  get_tuple_if_valid_t;

    public:
    typedef typename details::find_type_impl< index, typename get_tuple_if_valid_t::type >::type type;
};

}//end namespace util


#endif

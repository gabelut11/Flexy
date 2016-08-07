#ifndef MANIPULATE_TYPES_HPP
#define MANIPULATE_TYPES_HPP

#include <type_traits>
#include <tuple>
#include <utility>

namespace util
{

    namespace details
    {

    template<class T>
    struct identity_impl
    {
        typedef T type;
    };

    //------------------------------------------------------------------------------------------------------

    template< size_t n, class... Args>
    struct erase_first_n_impl;

    template < size_t n, template<class...> class Tuple >
    struct erase_first_n_impl<n, Tuple<> >
    {
        typedef Tuple<> type;
    };

    template < size_t n, class First, class... Args, template<class...> class Tuple >
    struct erase_first_n_impl < n, Tuple<First, Args...> >
    {
        static const size_t next_n = (n > 0) ? n-1 : 0;
        typedef erase_first_n_impl< next_n, Tuple<Args...> > next_t;

    public:
        typedef typename std::conditional < (n==0),  Tuple<First, Args...>,
            typename next_t::type >::type type;
    };

    //------------------------------------------------------------------------------------------------------

    template < size_t n, class... T>
    struct get_first_n_impl;

    template<size_t n, template<class...> class Tuple, class... R>
    struct get_first_n_impl<n, Tuple<>, R...>
    {
        typedef Tuple<R...> type;
    };

    template < size_t n, class First, class... Rest, template < class... > class Tuple, class... Result >
    struct get_first_n_impl < n, Tuple<First, Rest...>, Result... >
    {
        static const size_t next_n = (n > 0) ? n-1 : 0;
        typedef get_first_n_impl< next_n, Tuple<Rest...>, Result..., First > next_t;

    public:
        typedef typename std::conditional< (n == 0), Tuple<Result...>,
            typename next_t::type >::type type;
    };

    //-----------------------------------------------------------------------------------------------------

    template < size_t n, class... T>
    struct get_last_n_impl;

    template<size_t n, template<class...> class Tuple>
    struct get_last_n_impl<n, Tuple<>>
    {
        typedef Tuple<> type;
    };

    template<size_t n, class... Args, template<class...> class Tuple>
    struct get_last_n_impl<n, Tuple<Args...>>
    {
        private:
        const static size_t size = sizeof...(Args);

        public:
        typedef typename std::conditional< (n >= size), Tuple<Args...>,
                typename erase_first_n_impl<size-n, Tuple<Args...>>::type>::type type;
    };

    //------------------------------------------------------------------------------------------------------

    template<size_t n, class... Args>
    struct erase_last_n_impl;

    template<size_t n, template<class...> class Tuple>
    struct erase_last_n_impl<n, Tuple<>>
    {
        typedef Tuple<> type;
    };

    template<size_t n, class... Args, template<class...> class Tuple>
    struct erase_last_n_impl<n, Tuple<Args...> >
    {
    private:
        static const size_t size = sizeof...(Args);
        typedef std::conditional< (n>=size),  Tuple<>,
        typename get_first_n_impl< size-n, Tuple<Args...>>::type > next_t;
    public:
        typedef typename std::conditional< (n==0),  Tuple<Args...>, typename next_t::type >::type type;
    };

    //------------------------------------------------------------------------------------------------------


    template< size_t min, size_t max, class... Args>
    struct get_range_impl;

    template < size_t min, size_t max, template<class...> class Tuple, class... Rest >
    struct get_range_impl<min, max, Tuple<>, Rest... >
    {
        typedef Tuple<Rest...> type;
    };

    template<size_t min, size_t max, class First, class... Args, template<class...> class Tuple,  class... Rest>
    struct get_range_impl< min, max,  Tuple<First, Args...>, Rest... >
    {
    private:
        const static size_t size = sizeof...(Args) + 1;
        const static size_t stop = (max > size) ? size : max;
        const static size_t start = (min > stop) ? stop : min;
        typedef Tuple<First, Args...> tuple_t;
        typedef erase_last_n_impl< size-stop, typename erase_first_n_impl<start, tuple_t>::type > result_t;

    public:
        typedef typename std::conditional< (start == stop), Tuple<>, typename result_t::type >::type type;
    };

    //------------------------------------------------------------------------------------------------------

    template< size_t initial_size, class T, class... Args>
    struct find_index_impl;

    template< size_t initial_size, class T, template<class...> class Tuple, class First, class... Args>
    struct find_index_impl<initial_size, T, Tuple<First, Args...>>
    {
    private:
        static const size_t current_size = sizeof...(Args) + 1;
        static const bool   type_found = std::is_same<T, First>::value;

        typedef std::integral_constant<int, initial_size - current_size> 	index_wrapper_t;
        typedef find_index_impl<initial_size, T, Tuple<Args...>> 		next_iteration_t;

        typedef std::conditional< type_found, index_wrapper_t, next_iteration_t> result_t;

    public:
        static const int value = result_t::type::value;
    };

    template<size_t initial_size, class T, template<class...> class Tuple>
    struct find_index_impl<initial_size, T, Tuple<>>
    {
        static const int value = -1;
    };

    //----------------------------------------------------------------------------------------------------------

    template<size_t index, class Enabled>
    struct find_type_impl;

    template<size_t index, template<class...> class Tuple, class First, class... Args>
    struct find_type_impl<index, Tuple<First, Args...>>
    {
    private:
        typedef identity_impl<First> found_type_wrapper_t;
        typedef find_type_impl<index-1, Tuple<Args...>> next_iteration_t;
        typedef typename std::conditional< (index==0), found_type_wrapper_t, next_iteration_t>::type result_t;

    public:
        typedef typename result_t::type type;
    };

    //------------------------------------------------------------------------------------------------------

    template<class Tuple, template<class> class Fun, class... Result>
    struct transform_impl;

    template<class First, class... Args, template<class> class Fun, class... Result>
    struct transform_impl< std::tuple<First, Args...>, Fun, Result...>
    {
        typedef typename Fun<First>::type arg_t;
        typedef typename transform_impl<std::tuple<Args...>, Fun, arg_t>::type type;
    };

    template<class LastArg, template<class> class Fun, class... Result>
    struct transform_impl< std::tuple<LastArg>, Fun, Result...>
    {
        typedef typename Fun<LastArg>::type last_arg_t;
        typedef std::tuple<Result..., last_arg_t> type;
    };

    //------------------------------------------------------------------------------------------------------

    template< template<class...> class To, class... T >
    struct transfer_all_impl
    {
        typedef To<T...> type;
    };

    template <  template<class...> class To,  template<class...> class From, class... T>
    struct transfer_all_impl< To, From<T...> >
    {
        typedef To<T...> type;
    };

    //------------------------------------------------------------------------------------------------------

    template< size_t n, template<class...> class To, class... Args >
    struct transfer_first_n_impl
    {
        private:
        typedef std::tuple<Args...> tuple_t;
        typedef typename get_first_n_impl<n, tuple_t>::type source_t;

        public:
        typedef typename transfer_all_impl< To, source_t >::type type;
    };

    template < size_t n, template<class...> class To,  template<class...> class From, class... T >
    struct transfer_first_n_impl< n, To,  From<T...> >
    {
        private:
        typedef typename get_first_n_impl<n, From<T...>>::type source_t;

        public:
        typedef typename transfer_all_impl<To, source_t>::type type;
    };

    //------------------------------------------------------------------------------------------------------

    template< size_t n, template<class...> class To, class... Args >
    struct transfer_last_n_impl
    {
        private:
        typedef std::tuple<Args...> tuple_t;
        typedef typename get_last_n_impl< n, tuple_t>::type source_t;

        public:
        typedef typename transfer_all_impl< To, source_t>::type type;
    };

    //------------------------------------------------------------------------------------------------------

    }//end namespace details

}//namespace util


#endif //MANIPULATE_TYPES_HPP

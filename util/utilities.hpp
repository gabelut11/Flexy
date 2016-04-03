#ifndef UTIL_HPP
#define UTIL_HPP

#include <type_traits>
#include "types.hpp"
#include "details/create.hpp"
#include "details/manipulate.hpp"
#include "details/transform.hpp"

namespace util
{
	/**
	 * make_index
	 */
	template<size_t n>
	struct make_index
	{
		typedef typename details::make_index_impl<n>::type type;
	};

	/**
	 * transfer_all
	 */
	template< template<class...> class To, class... T >
	struct transfer_all : public details::transfer_all_impl<To, T...>
	{};

	/**
	 * transfer_first_n
	 */
	template< size_t n, template<class...> class To, class... T >
	struct transfer_first_n : public details::transfer_first_n_impl<n, To, T...>
	{};

	/**
	 * transfer_first_n
	 */
	template< size_t n, template<class...> class To, class... T >
	struct transfer_last_n : public details::transfer_last_n_impl< n, To, T...>
	{};

	/**
	 * transfer_n
	 */
	template< size_t index, size_t n, template<class...> class To, class... T >
	struct transfer_n : public details::transfer_n_impl<index, n, To, T...>
	{};

	/**
	 * erase_first_n
	 */
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

	/**
	 * erase_last_n
	 */
	template<size_t n, class... Args>
	struct erase_last_n;

	template<size_t n, class... Args, template<class...> class Tuple>
	struct erase_last_n<n, Tuple<Args...> >
	{
	public:
		typedef typename details::erase_last_n_impl<n, Tuple<Args...>>::type type;

	};

	/**
	 * erase_n
	 */
	template<size_t index, size_t n, class T >
	struct erase_n;

	template<size_t index, size_t n, class... Args, template<class...> class Tuple >
	struct erase_n < index, n, Tuple<Args...> >
	{
		typedef typename details::erase_n_impl<index, n, Tuple<Args...>>::type type;
	};


	/**
	 * get_first_n
	 */
	template<size_t n, class T>
	struct get_first_n;

	template<size_t n, class... Args, template<class...> class Tuple>
	struct get_first_n<n, Tuple<Args...> >
	{
		typedef typename details::get_first_n_impl<n, Tuple<Args...>>::type type;
	};

	/**
	 * get_last_n
	 */
	template<size_t n, class T>
	struct get_last_n;

	template<size_t n, class... Args, template<class...> class Tuple>
	struct get_last_n<n, Tuple<Args...>>
	{
		typedef typename details::get_last_n_impl<n, Tuple<Args...>>::type type;
	};

	/**
	 * get_n
	 */
	template<size_t index, size_t n, class T>
	struct get_n;

	template<size_t index, size_t n, class... Args, template<class...> class Tuple>
	struct get_n<index, n, Tuple<Args...>>
	{
		typename details::get_n_impl<index, n, Tuple<Args...>>::type type;
	};

	/**
	 * get_range
	 */
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

	/**
	 * add
	 */
	template<class... Args>
	struct add
	{
		typedef typename details::add_impl<Args...>::type type;
	};

	/**
	 * transform
	 */
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

	/**
	 * find_index
	 */
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

	/**
	 * find_type
	 */
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

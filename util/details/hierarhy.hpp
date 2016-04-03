#ifndef HIERARCHY_HPP
#define HIERARCHY_HPP

#include "manipulate.hpp"

namespace details
{

	template<class...>
	struct left_base;

	template< template<class...> class Tuple, class First, class... Args>
	struct left_base< Tuple<First, Args...> > :	public transfer_first_n_impl < sizeof...(Args), Tuple,  First, Args...>::type
	{
		typedef typename transfer_first_n_impl < sizeof...(Args), Tuple,  First, Args...>::type type;
	};

	template< template<class...> class Tuple, class Last>
	struct left_base< Tuple<Last> > : public Tuple<Last>
	{
		typedef Tuple<Last> type;
	};

	template<class...>
	struct right_base;

	template< template<class...> class Tuple, class First, class... Args>
	struct right_base< Tuple<First, Args...> > : public transfer_last_n_impl < 1, Tuple, First, Args...>::type
	{
		typedef typename transfer_last_n_impl < 1, Tuple, First, Args...>::type type;
	};

	template< template<class...> class Tuple, class Last>
	struct right_base< Tuple<Last> > :	public Tuple<Last>
	{
		typedef Tuple<Last> type;
	};

	template<size_t index, class...>
	struct subobject_impl;

	template<size_t index, class... Args, template<class...> class Hierarchy>
	struct subobject_impl<index, Hierarchy<Args...> >
	{
		static_assert(sizeof...(Args) > 0, "invalid type list");
		static_assert(index < sizeof...(Args), "invalid index value");

		typedef typename details::left_base<Hierarchy<Args...>>::type left_base_t;
		typedef typename details::right_base<Hierarchy<Args...>>::type right_base_t;

		static const size_t num_iterations = sizeof...(Args) - index;
		typedef subobject_impl<index, left_base_t> next_t;
		typedef typename std::conditional<(num_iterations == 1), details::identity_impl<right_base_t>, next_t>::type result_t;

	public:
		typedef typename result_t::type type;
	};


}//end namespace details

#endif

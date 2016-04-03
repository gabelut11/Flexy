#ifndef TRANSFORM_TYPES_HPP
#define TRANSFORM_TYPES_HPP

#include <type_traits>
#include <tuple>

namespace details
{

	/**
	 * utility for util::transform
	 */
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

}//namespace details


#endif //TRANSFORM_TYPES_HPP

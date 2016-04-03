#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "util/generate_hierarchy.hpp"
#include "util/creation_policy.hpp"
#include <tuple>

namespace Flexy
{

	template< class... Args >
	struct factory;

	template<class First, class... Rest >
	struct factory<First, Rest...> : util::generate_hierachy< factory, First, Rest...>
	{
		typedef std::tuple<First, Rest...> 	types_t;

		template<void* (&Allocator)(size_t) = operator new>
		struct create_on_heap
		{
			template<class T, class... Args>
			static T * create(Args&&... args)
			{
				static const size_t index = util::find_index<T, types_t>::value;
				static_assert(index >=0, "invalid type");

				typedef typename util::subobject<index, factory<First, Rest...> >::type subobject_t;
				typedef typename subobject_t::template create_on_heap<Allocator> creator_t;
				return (creator_t::template create<T>(std::forward<Args>(args)...));
			}
		};

		struct create_in_place
		{
			template<class T, class... Args>
			static T * create(void* ptr, Args&&... args)
			{
				static const size_t index = util::find_index<T, types_t>::value;
				static_assert(index >=0, "invalid type");

				typedef typename util::subobject<index, factory<First, Rest...>>::type subobject_t;
				typedef typename subobject_t::create_in_place creator_t;
				return (creator_t::template create<T>(ptr, std::forward<Args>(args)...));
			}
		};

		template<template<class...> class SmartPtrType, void* (&Allocator)(size_t) = operator new, class... SmartPtrArgs>
		struct create_smart_ptr
		{
			template<class T, class... Args>
			static SmartPtrType<T, SmartPtrArgs...> create(Args&&... args)
			{
				static const size_t index = util::find_index<T, types_t>::value;
				static_assert(index >=0, "invalid type");

				typedef typename util::subobject<index, factory<First, Rest...>>::type subobject_t;
				typedef typename subobject_t:: template create_smart_ptr<SmartPtrType, Allocator, SmartPtrArgs...> creator_t;
				return (creator_t::template create<T>(std::forward<Args>(args)...));
			}
		};

	};

	template < class Result >
	struct factory < Result >
	{
		template<void* (&Allocator)(size_t) = operator new>
		struct create_on_heap
		{
			template<class T, class... Args>
			static Result * create(Args&&... args)
			{
				typedef typename util::construct<T>::template on_heap<Allocator> creator_t;
				return creator_t::create(std::forward<Args>(args)...);
			}
		};

		struct create_in_place
		{
			template<class T, class... Args>
			static Result * create(void* ptr, Args&&... args)
			{
				typedef typename util::construct<T>::in_place creator_t;
				return creator_t::create(ptr, std::forward<Args>(args)...);
			}
		};

		template<template<class...> class SmartPtrType, void* (&Allocator)(size_t) = operator new, class... SmartPtrArgs>
		struct create_smart_ptr
		{
			template<class T, class... Args>
			static SmartPtrType<Result, SmartPtrArgs...> create(Args&&... args)
			{
				typedef typename util::construct<T>:: template smart_ptr<SmartPtrType, Allocator, SmartPtrArgs...> creator_t;
				return creator_t::create(std::forward<Args>(args)...);
			}
		};
	};



}//end namespace Flexy

#endif

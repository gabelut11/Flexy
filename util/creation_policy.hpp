#ifndef CREATION_POLICY_HPP
#define CREATION_POLICY_HPP

namespace util
{
	template< class Result, class... Args>
	struct construct;

	template<class Ret>
	struct construct<Ret>
	{
		template<void* (&Allocator)(size_t) = operator new>
		struct on_heap
		{
			template<class... Args>
			static Ret* create(Args&&... args)
			{
				void *ptr = Allocator(sizeof(Ret));
				new(ptr) Ret(std::forward<Args>(args)...);
				return (Ret*)ptr;
			}
		};

		struct in_place
		{
			template<class... Args>
			static Ret* create(void *& ptr, Args&&... args)
			{
				new(ptr) Ret(std::forward<Args>(args)...);
				return (Ret*)ptr;
			}

			template<class... Args>
			static Ret* create(Ret *& ptr, Args&&... args)
			{
				new(ptr) Ret(std::forward<Args>(args)...);
				return Ret((Ret*)ptr);
			}
		};

		template<template<class...> class SmartPtrType, void* (&Allocator)(size_t) = operator new, class... SmartPtrArgs>
		struct smart_ptr
		{
			template<class... Args>
			static SmartPtrType<Ret, SmartPtrArgs...> create(Args&&... args)
			{
				void *ptr = Allocator(sizeof(Ret));
				new(ptr) Ret(std::forward<Args>(args)...);

				typedef SmartPtrType<Ret, SmartPtrArgs...> Result_t;
				return Result_t((Ret*)ptr);
			}
		};
	};

	template< class Allocator>
	void* allocate(size_t n)
	{
		static Allocator allocator;
		return allocator.allocate(n);
	}


}//namespace util

#endif //CREATION_POLICY_HPP

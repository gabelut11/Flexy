#ifndef ABSTRACT_FACTORY_HPP
#define ABSTRACT_FACTORY_HPP

#include "util/generate_hierarchy.hpp"
#include "util/creation_policy.hpp"
#include "factory.hpp"
#include "utilities.hpp"
#include <tuple>

namespace Flexy
{
template<class... AbstractProducts>
struct abstract_factory
{
    template<class... ConcreteProducts>
    struct create_concrete
    {
        typedef std::tuple<AbstractProducts...> abstract_products_t;
        typedef std::tuple<ConcreteProducts...> concrete_products_t;
        typedef factory<ConcreteProducts...>    factory_t;

        template<void* (&Allocator)(size_t) = operator new>
        struct on_heap
        {
            typedef typename factory_t:: template create_on_heap<Allocator> creator_t;
            template<class AbstractProduct, class... Args>
            static AbstractProduct *create(Args&&... args)
            {
                static const size_t index = util::find_index<AbstractProduct, abstract_products_t>::value;
                static_assert(index >= 0, "invalid type");

                typedef typename util::find_type<index, concrete_products_t>::type concrete_type_t;
                AbstractProduct *result = creator_t:: template create<concrete_type_t>(std::forward<Args>(args)...);
                return result;
            }
        };

        struct in_place
        {
            typedef typename factory_t::create_in_place creator_t;

            template<class AbstractProduct, class... Args>
            static AbstractProduct * create(void* ptr, Args&&... args)
            {
                static const size_t index = util::find_index<AbstractProduct, abstract_products_t>::value;
                static_assert(index >=0, "invalid type");

                typedef typename util::find_type<index, concrete_products_t>::type concrete_type_t;
                AbstractProduct *result = creator_t:: template create<concrete_type_t>(std::forward<Args>(args)...);
                return result;
            }
        };

        template<template<class...> class SmartPtrType, void* (&Allocator)(size_t) = operator new, class... SmartPtrArgs>
        struct smart_ptr
        {
            typedef typename factory_t:: template create_smart_ptr<SmartPtrType, Allocator> creator_t;

            template<class AbstractProduct, class... Args>
            static SmartPtrType<AbstractProduct, SmartPtrArgs...> create(Args&&... args)
            {
                    static const size_t index = util::find_index<AbstractProduct, abstract_products_t>::value;
                    static_assert(index >=0, "invalid type");

            typedef typename util::find_type<index, concrete_products_t>::type concrete_type_t;
                    return creator_t:: template create<concrete_type_t>(std::forward<Args>(args)...);
            }
        };
    };

};

template<class AbstractProduct>
struct abstract_factory<AbstractProduct>
{
    template<class ConcreteProduct>
    struct create_concrete
    {
        typedef factory<ConcreteProduct> factory_t;

        template<void* (&Allocator)(size_t) = operator new>
        struct on_heap
        {
            typedef typename factory_t:: template create_on_heap<Allocator> creator_t;

            template<class Product, class... Args>
            static AbstractProduct *create(Args&&... args)
            {
                AbstractProduct *result = creator_t::template create<ConcreteProduct>(std::forward<Args>(args)...);
                return result;
            }
        };

        struct in_place
        {
            typedef typename factory_t::create_in_place creator_t;

            template<class Product, class... Args>
            static AbstractProduct *create(void* ptr, Args&&... args)
            {
                AbstractProduct *result = creator_t::template create<ConcreteProduct>(std::forward<Args>(args)...);
                return result;
            }
        };

        template<template<class...> class SmartPtrType, void* (&Allocator)(size_t) = operator new, class... SmartPtrArgs>
        struct smart_ptr
        {
            typedef typename factory_t:: template create_smart_ptr<SmartPtrType, Allocator> creator_t;

            template<class Product, class... Args>
            static SmartPtrType<AbstractProduct, SmartPtrArgs...> create(Args&&... args)
            {
                return creator_t:: template create<ConcreteProduct>(std::forward<Args>(args)...);
            }
        };

    };//end concrete_factory
};


}//namespace Flexy

#endif //ABSTRACT_FACTORY_HPP

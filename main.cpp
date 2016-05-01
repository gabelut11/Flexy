/* 
 * File:   main.cpp
 * Author: gabi
 *
 * Created on April 3, 2016, 5:04 PM
 */

#include <cstdlib>
#include <tuple>
#include <type_traits>

#include <iostream>
#include <bitset>

#include "util/generate_hierarchy.hpp"
#include "util/details/hierarhy.hpp"
#include "util/creation_policy.hpp"
#include "util/creation_policy2.h"
#include "concrete_factory.h"
#include <memory>
#include <string>

using namespace std;

//void* (&Allocator)(size_t) = operator new

struct A{};
struct B{};
struct C{};
struct D{};

int main(int argc, char** argv) {

    using namespace Flexy;
    using namespace util;
    using my_factory1 =  factory< creation_type::on_heap>::create<A, B>::type;
    using my_factory2 =  factory< creation_type::on_heap>::create<A, B, C>::type;

  
    my_factory1 *p1 = new my_factory2;
 
    p1->create<A>();
    p1->create<B>();

    
    
    return 0;
}


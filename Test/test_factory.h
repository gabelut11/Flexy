/* 
 * File:   test_factory.h
 * Author: gabi
 *
 * Created on April 17, 2016, 2:16 PM
 */

#ifndef TEST_FACTORY_H
#define	TEST_FACTORY_H

#include "../factory.hpp"
#include "TypesForTesting.h"
#include <memory>
#include <iostream>

namespace Testing
{
    using namespace std;
    typedef Flexy::factory< Bread, Pretzel> small_shop_t;
    
    typedef Flexy::factory<Bread, Pretzel, Bagel> small_shop_extended;
    
    typedef Flexy::factory<Bagel> baker;

    
    
    
    void test()
    {
        small_shop_t *s1 = new small_shop_extended;
        
        baker *b = new small_shop_extended;
        
    }
    

}//end namespace Testing

#endif	/* TEST_FACTORY_H */


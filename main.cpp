/*
 * File:   main.cpp
 * Author: gabi
 *
 * Created on April 3, 2016, 5:04 PM
 */

#include <cstdlib>
#include <memory>
#include <string>

#include <iostream>
#include "generate/generate_factory.hpp"
#include "generate/details/creation/options.hpp"

#include "concrete_factory.h"

#include "generate/generate_hierarchy.hpp"
#include "generate/details/creation/options.hpp"
#include "abstract_factory.hpp"

using namespace std;


/*
    Factory

    -> Generates a hierarchy of classes and a factory at the same time in a single line of code.
       For example this line generates a factory that knows how to create types A and B.

        typedef generate_factory< creation::on_heap>::that_creates<A, B>::type AB_Factory;

    -> You can customize how the object is created:
        - on heap: creation::on_heap
        - inside an allready allocated memory: creation::in_place
        - inside a smart_ptr:
        typedef generate_factory< creation::smart_ptr, std::unique_ptr>::that_creates<A>::type fact_t;

    -> The constructors of A and B may have different prototypes (different number of parameters
       and different type of parameters). For instance A may have defined a constructor with two
       parameters and a default constructor and B can have a constructor with three parameters.

        struct A {
            A();
            A(int, bool);
        };

        struct B {
            B(const std::string&, float, int);
        };

        AB_Factory factory;
        factory.create<A>();
        factory.create<A>(8, true);

        factory.create<B>(my_string, 6.8, 9);

    -> If the parameters are wrong or we want to build a type that does't exist in the list it won't compile.
        //factory.create<B>(); //compile error

        struct Z{
            Z(int);
        };
        //factory.create<Z>(8); //won't compile. The list of types that can be created with AB_Factory is only A & B (::that_creates<A, B>)



    -> If, after a while we want the factory to create, besides A and B, another type C is not necessary to modify the original factory
       (Factory_AB) as is usually done. Nor must recompile code that already uses Factory_AB.

        We create a new factory with:
        typedef generate_factory< creation::on_heap>::that_creates<A, B, C>::type ABC_Factory;

        The new factory inherits from Factory_AB. So it can be used is places where Factory_AB was used.
        When declaring a factory like Factory_ABC the follwing hierarchyis created:

            Factory_A       Factory_B
                |               |
                -----------------
                        |
                    Factory_AB      Factory_C
                        | 	           |
                        ---------------
                                |
                            Factory_ABC

            So we can have:

            //hpp
            struct SomeClass
            {
                SomeClass(Factory_AB*);
                Factory_AB *factory;

            };

            //cpp
            SomeClass::SomeClass(Factory_AB* f): factory(f){}

            Factory_AB *f = new Factory_AB;
            SomeClass obj(f);

        We can leave the member of type Factory_AB, as it is. We don't have to modify the interface.
        We'll assign in the constructor's implementation a Factory_ABC, instead of Factory_AB.

            Factory_AB *f = new Factory_ABC;
            SomeClass obj(f);

    --> Also the new factory converts into a "smaller" factory, so we can reduce the factory when we want.
        If we want in certain places to construct only C objects with Factory_ABC:

        //Create factory that constructs A, B, C:
            Factory_ABC *abc = new Factory_ABC;

        //We want to limit fuctionality here and construct ony C:
            typedef	generate_factory< creation::on_heap>::that_creates<C>::type Factory_C;
            Factory_C *factory_c = abc;  //creates A, B, C

            some_function_that_can_handle_only_C(factory_c);

        //We want to create only A's
            typedef	generate_factory< creation::on_heap>::that_creates<A>::type Factory_A;
            Factory_A *factory_a2 = abc;

*/

/*
    Abstract Factory

    -> It is used for creating families of objects belonging to an inheritance hierarchy.
    -> Let's say we have two families of objects:

              A                           B
              |                           |
         DerivedFromA                DerivedFromB
              |                           |
        MoreDerivedFromA            MoreDerivedFromB

    -> We want to use those objects in apolymorphic way. So we only want to handle objects through pointers to A and B.
    -> We can create a factory that creates concrete types DerivedFromA and DerivedFromB, but returns pointers to A and B:

    typedef
        generate_abstract_factory<creation::on_heap>::of<A, B>::that_creates<DerivedFromA, DerivedFromB>::type
            Abstr_AB;

        Abstr_AB abstr_ab;
        A *ptr_A = abstr_ab.create<A>(); //creates an object of type DerivedFromA and return a pointer to A

    -> Abstract Factory has the same features as Factory :
        - creation policy (on_heap, in_place, smart_ptr).
        - Abstract Factory that creates more than an object type belogs to a hierarchy of factories

        e.g:
        typedef
        generate_abstract_factory<creation::on_heap>::of<A, B, C>::that_creates< DerivedFromA,
                                                                                         DerivedFromB,
                                                                                         DerivedFromC>::type Factory_ABC;

     Factory_A       Factory_B
        |               |
        -----------------
                |
            Factory_AB     Factory_C
                | 	           |
                ---------------
                       |
                  Factory_ABC
*/

struct A {
    A()          { cout << "A()" << endl; }
    A(int, bool) { cout << "A(int,bool)" << endl;      }
};
struct B {
    B() { cout << "B()" << endl; }
    B(const std::string&, float, int) { cout << "B(const std::string&, float, int)" << endl; }
};
struct C { C() { cout << "C()" << endl; } };

struct DerivedFromA: public A {
    DerivedFromA()          { cout << "DerivedFromA()" << endl; }
    DerivedFromA(int, bool) { cout << "DerivedFromA(int,bool)" << endl;      }
};

struct DerivedFromB: public B {
    DerivedFromB() { cout << "DerivedFromB()" << endl; }
    DerivedFromB(const std::string&, float, int) { cout << "DerivedFromB(const std::string&, float, int)" << endl; }
};

struct DerivedFromC: public C { DerivedFromC() { cout << "DerivedFromC()" << endl; } };


int main(int argc, char** argv) {

    using namespace Flexy;

    cout << "------------------ Factory -----------------------------" << endl <<endl;

    using Factory_AB =  generate_factory<creation::on_heap>::that_creates<A, B>::type;

    std::unique_ptr<Factory_AB> f_ab;
    f_ab.reset(new Factory_AB);
    f_ab->create<A>();
    f_ab->create<A>(8, true);
    f_ab->create<B>("hey", 7.8, 3);

    cout << "--------------------------------------------------------" << endl;

    using Factory_ABC =  generate_factory< creation::on_heap>::that_creates<A, B, C>::type;
    Factory_ABC *f_abc = new Factory_ABC;
    f_abc->create<A>();
    f_abc->create<A>(7, false);
    f_abc->create<C>();

    f_ab.reset(f_abc);

    cout << "--------------------------------------------------------" << endl;


    using factory_smart_ptrs = generate_factory<creation::smart_ptr, std::unique_ptr>::that_creates<A, B>::type;

    factory_smart_ptrs f_sp;
    std::unique_ptr<A> ap = f_sp.create<A>();
    std::unique_ptr<B> bp = f_sp.create<B>("hallo", 1.2, 55);


    cout << "------------------ Abstract Factory -----------------------------" << endl <<endl;


   typedef
   generate_abstract_factory<creation::on_heap>::of<A, B>::that_creates<DerivedFromA, DerivedFromB>::type Abstr_AB;

    Abstr_AB abstr_ab;
    A *ptr_A = abstr_ab.create<A>();
    delete ptr_A;

    B *ptr_B = abstr_ab.create<B>("creating DerivedFromB", 7.0, 10);
    delete ptr_B;

    return 0;
}


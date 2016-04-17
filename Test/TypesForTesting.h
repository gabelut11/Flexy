/* 
 * File:   Types.h
 * Author: gabi
 *
 * Created on April 17, 2016, 2:18 PM
 */

#ifndef TYPES_FOR_TESTING_H
#define	TYPES_FOR_TESTING_H

namespace Testing
{

    using namespace std;

//------------------------------------------------------------------------------
    
struct Bread 
{
    Bread()             { cout << "Created Bread." << endl;         }
    virtual ~Bread()    { cout << "Bread destroyed." << endl;       }
};

struct Pretzel 
{
    Pretzel()                    { cout << "Created  Pretzel. " << endl; }
    Pretzel(const char* with)    { cout << "Created  Pretzel with " << with << endl; }
    virtual ~Pretzel()           { cout << "Pretzel destroyed." << endl;   }
};

struct Bagel 
{
    Bagel()                     { cout << "Created  Bagel." << endl;      }
    Bagel(const char *with)     { cout << "Created  Bagel with " << with << endl; }
    virtual ~Pretzel()          { cout << "Bagel destroyed." << endl;   }
};

struct Cake
{
    Cake()                  { cout << "Created Cake." << endl;     }
    Cake(const char* with)  { cout << "Created Cake with " << with << endl; }
    virtual ~Cake()         { cout << "Cake destroyed." << endl;   }
};

//------------------------------------------------------------------------------

struct Baguette : public Bread 
{
    Baguette()             { cout << "Created Baguette." << endl;         }
    virtual ~Baguette()    { cout << "Baguette destroyed." << endl;   }
};

struct PretzelWithSalt : public Pretzel 
{
    Baguette()             { cout << "Created PretzelWithSalt." << endl;         }
    virtual ~Baguette()    { cout << "PretzelWithSalt destroyed." << endl;   }
};

struct BagelWithCaraway : Bagel
{
    BagelWithCaraway()             { cout << "Created BagelWithCaraway." << endl;         }
    virtual ~BagelWithCaraway()    { cout << "BagelWithCaraway  destroyed." << endl;   }
};

//------------------------------------------------------------------------------

struct Cheesecake : Cake
{
    Cheesecake()             { cout << "Created Cheesecake." << endl;         }
    virtual ~Cheesecake()    { cout << "Cheesecake destroyed." << endl;   }
};

struct Muffin : Cake
{
    Muffin()             { cout << "Created Muffin." << endl;         }
    virtual ~Muffin()    { cout << "Muffin destroyed." << endl;   }
};

struct Brownie : Cake
{
    Brownie()             { cout << "Created Brownie." << endl;         }
    virtual ~Brownie()    { cout << "Brownie destroyed." << endl;   }
};

struct CarrotCake : Cake
{
    CarrotCake()             { cout << "Created CarrotCake." << endl;         }
    virtual ~CarrotCake()    { cout << "CarrotCake destroyed." << endl;   }
};

struct ChocolateCake : Cake
{
    ChocolateCake()             { cout << "Created ChocolateCake." << endl;         }
    virtual ~ChocolateCake()    { cout << "ChocolateCake  destroyed." << endl;   }
};

}//end namespace  Testing


#endif	/* TYPES_FOR_TESTING_H */


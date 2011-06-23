#include <string>
#include "TObjFactory.hpp"

class Base {
public:
     virtual void test(void) = 0;
};
 
class classA : public Base {
public:
     virtual void test(void) { std::cout << 'A' << std::endl; }
};
 
class classB : public Base {
public:
     virtual void test(void) { std::cout << 'B' << std::endl; }
};
 
int main(void) {
     TObjFactory<std::string,Base> myFactory;
     myFactory.registerBuilder("A", TypeID<classA>());
     myFactory.registerBuilder("B", TypeID<classB>());
 
     Base* auA(myFactory.buildObj("A"));
     Base* auB(myFactory.buildObj("B"));
 
     auA->test();
     auB->test();

     delete auA;
     delete auB;
    
     return 0;
}


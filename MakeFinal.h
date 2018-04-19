#ifndef _MAKE_FINAL_H
#define _MAKE_FINAL_H
#include <iostream>
/*
Prevent a class from being inherited (make it final).
https://www.geeksforgeeks.org/simulating-final-class-in-c/
 */
namespace MakeFinal
{
    class MyFinalClass;
    class Final
    {
    private:
        Final(){ std::cout << "Final::ctor" << std::endl; }
        friend class MyFinalClass; //so that MyFinalClass::ctor can call Final::ctor
    };
    class MyFinalClass : virtual Final //either virtual public or virtual private (default): make Derived::ctor call Final::ctor
    {                                   //without virtual inheritance: Derived::ctor calls MyFinalClass::ctor which calls Final::ctor, no problem
    public:
        MyFinalClass(){ std::cout << "MyFinalClass::ctor" << std::endl; }
    };

    /*
    class Derived : public MyFinalClass // Compile Error: because Derived::ctor calls Final::ctor, which is private
    {
    public:
        Derived(){ std::cout << "Derived::ctor" << std::endl; }
    };
    */

    void Test()
    {
        MyFinalClass mfc;
        //Derived d;
    }


    class Base
    {
    public:
        Base(){ std::cout << "Base::ctor" << std::endl; }
        virtual ~Base() = 0;
    };
    Base::~Base() { std::cout << "Base::dtor" << std::endl; }
    class Derived1 : virtual public Base
    {
    public:
        Derived1(){ std::cout << "Derived1::ctor" << std::endl; }
        ~Derived1(){ std::cout << "Derived1::dtor" << std::endl; }
    };
    class Derived2 : virtual public Base
    {
    public:
        Derived2(){ std::cout << "Derived2::ctor" << std::endl; }
        ~Derived2(){ std::cout << "Derived2::dtor" << std::endl; }
    };
    class Join : public Derived1, public Derived2
    {
    public:
        Join(){ std::cout << "Join::ctor" << std::endl; }
        ~Join() { std::cout << "Join::dtor" << std::endl; }
    };
    void Test2()
    {
        Base * d1 = new Derived1;
        delete d1;
        Base * j = new Join;
        delete j;
    }
}
#endif

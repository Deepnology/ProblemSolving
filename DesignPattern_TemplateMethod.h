#ifndef _DESIGN_PATTERN_TEMPLATE_METHOD_H
#define _DESIGN_PATTERN_TEMPLATE_METHOD_H
#include "Debug.h"
namespace DesignPattern_TemplateMethod
{
    class Base
    {
        void Method1(){ std::cout << "Base::Method1" << std::endl; }
        void Method2(){ std::cout << "Base::Method2" << std::endl; }
        void Method3(){ std::cout << "Base::Method3" << std::endl; }
    public:
        virtual void PlaceHolderMethod1() = 0;
        virtual void PlaceHolderMethod2() = 0;
        void Execute()
        {
            //execute a template of methods
            //defer the exact steps of an algorithm to derived class
            std::cout << "Execute a template of 5 methods:" << std::endl;
            Method1();
            PlaceHolderMethod1();
            Method2();
            PlaceHolderMethod2();
            Method3();
            std::cout << std::endl;
        }
    };
    class Derived1 : public Base
    {
        void PlaceHolderMethod1(){ std::cout << "Derived1::PlaceHolderMethod1" << std::endl; }
        void PlaceHolderMethod2(){ std::cout << "Derived1::PlaceHolderMethod2" << std::endl; }
    };
    class Derived2: public Base
    {
        void PlaceHolderMethod1(){ std::cout << "Derived2::PlaceHolderMethod1" << std::endl; }
        void PlaceHolderMethod2(){ std::cout << "Derived2::PlaceHolderMethod2" << std::endl; }
    };

    void Test()
    {
        Derived1 d1;
        Derived2 d2;
        d1.Execute();
        d2.Execute();
    }
}
/*
Execute a template of 5 methods:
Base::Method1
Derived1::PlaceHolderMethod1
Base::Method2
Derived1::PlaceHolderMethod2
Base::Method3

Execute a template of 5 methods:
Base::Method1
Derived2::PlaceHolderMethod1
Base::Method2
Derived2::PlaceHolderMethod2
Base::Method3

 */
#endif

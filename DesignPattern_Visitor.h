#ifndef _DESIGN_PATTERN_VISITOR_H
#define _DESIGN_PATTERN_VISITOR_H
#include "Debug.h"
namespace DesignPattern_Visitor
{
    class VisitorBase;
    class Base
    {
    public:
        virtual void Accept(VisitorBase &) = 0;
        virtual ~Base() = 0;
    };
    Base::~Base(){ std::cout << "Base::dtor" << std::endl; }//Base::~Base() must be provided !!

    class Derived1 : public Base
    {
    public:
        void Accept(VisitorBase &);
        std::string GetDerived1() { return "Derived1"; }
        ~Derived1(){ std::cout << "Derived1::dtor" << std::endl; }
    };
    class Derived2 : public Base
    {
    public:
        void Accept(VisitorBase &);
        std::string GetDerived2() { return "Derived2"; }
        ~Derived2(){ std::cout << "Derived2::dtor" << std::endl; }
    };
    class Derived3 : public Base
    {
    public:
        void Accept(VisitorBase &);
        std::string GetDerived3() { return "Derived3"; }
        ~Derived3(){ std::cout << "Derived3::dtor" << std::endl; }
    };

    class VisitorBase
    {
    public:
        virtual void Visit(Derived1 *) = 0;
        virtual void Visit(Derived2 *) = 0;
        virtual void Visit(Derived3 *) = 0;
    };

    void Derived1::Accept(VisitorBase & v)
    {
        v.Visit(this);//invoke VisitorBase::Vist(Derived1 *)
    }
    void Derived2::Accept(VisitorBase & v)
    {
        v.Visit(this);//invoke VisitorBase::Vist(Derived2 *)
    }
    void Derived3::Accept(VisitorBase & v)
    {
        v.Visit(this);//invoke VisitorBase::Vist(Derived3 *)
    }


    class VisitorDerived1 : public VisitorBase
    {
        void Visit(Derived1 * d1)
        {
            std::cout << "VisitorDerived1 visit " << d1->GetDerived1() << std::endl;
        }
        void Visit(Derived2 * d2)
        {
            std::cout << "VisitorDerived1 visit " << d2->GetDerived2() << std::endl;
        }
        void Visit(Derived3 * d3)
        {
            std::cout << "VisitorDerived1 visit " << d3->GetDerived3() << std::endl;
        }
    };
    class VisitorDerived2 : public VisitorBase
    {
        void Visit(Derived1 * d1)
        {
            std::cout << "VisitorDerived2 visit " << d1->GetDerived1() << std::endl;
        }
        void Visit(Derived2 * d2)
        {
            std::cout << "VisitorDerived2 visit " << d2->GetDerived2() << std::endl;
        }
        void Visit(Derived3 * d3)
        {
            std::cout << "VisitorDerived2 visit " << d3->GetDerived3() << std::endl;
        }
    };

    void Test()
    {
        std::vector<Base *> v({new Derived1, new Derived2, new Derived3});
        VisitorDerived1 visitor1;
        for (auto & b : v)
            b->Accept(visitor1);
        VisitorDerived2 visitor2;
        for (auto & b : v)
            b->Accept(visitor2);
        for (auto & b : v)
            { delete b; b = nullptr; }
    }
}
#endif

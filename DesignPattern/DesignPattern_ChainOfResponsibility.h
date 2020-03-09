#ifndef _DESIGN_PATTERN_CHAIN_OF_RESPONSIBILITY_H
#define _DESIGN_PATTERN_CHAIN_OF_RESPONSIBILITY_H
#include "Debug.h"
namespace DesignPattern_ChainOfResponsibility
{
    class Employee
    {
    protected:
        Employee * m_next;
    public:
        Employee():m_next(NULL){}
        virtual ~Employee() = 0;
        virtual void Handle(){}
        void Add(Employee * next)
        {
            if (m_next)
                m_next->Add(next);
            else
                m_next = next;
        }
        void SetNext(Employee * next)
        {
            m_next = next;
        }
    };
    Employee::~Employee() {}
    class Respondent : public Employee
    {
    public:
        Respondent():Employee(){}
        ~Respondent(){}
        void Handle()
        {
            if (rand() % 3 == 0)
            {
                std::cout << "Respondent Pass->" << std::endl;
                m_next->Handle();
            }
            else
            {
                std::cout << "Respondent Handle." << std::endl;
            }
        }
    };
    class Manager : public Employee
    {
    public:
        Manager():Employee(){}
        ~Manager(){}
        void Handle()
        {
            if (rand() % 5 == 0)
            {
                std::cout << "Manager Pass->" << std::endl;
                m_next->Handle();
            }
            else
            {
                std::cout << "Manager Handle." << std::endl;
            }
        }
    };
    class Director : public Employee
    {
    public:
        Director():Employee(){}
        ~Director(){}
        void Handle()
        {
            if (rand() % 10 == 0)
            {
                std::cout << "Director Pass->" << std::endl;
                m_next->Handle();
            }
            else
            {
                std::cout << "Director Handle." << std::endl;
            }
        }
    };

    void Test()
    {
        Employee * respondent = new Respondent;
        Employee * manager = new Manager;
        Employee * director = new Director;

        respondent->SetNext(manager);
        manager->SetNext(director);
        director->SetNext(respondent);

        for (int i = 0; i < 20; ++i)
            respondent->Handle();

        delete respondent;
        delete manager;
        delete director;
    }
}
/*
Respondent Handle.
Respondent Handle.
Respondent Handle.
Respondent Handle.
Respondent Handle.
Respondent Handle.
Respondent Pass->
Manager Handle.
Respondent Handle.
Respondent Handle.
Respondent Pass->
Manager Pass->
Director Handle.
Respondent Handle.
Respondent Pass->
Manager Handle.
Respondent Handle.
Respondent Handle.
Respondent Handle.
Respondent Handle.
Respondent Pass->
Manager Handle.
Respondent Pass->
Manager Handle.
Respondent Handle.
Respondent Pass->
Manager Handle.
 */
#endif

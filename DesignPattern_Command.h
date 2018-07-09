#ifndef _DESIGN_PATTERN_COMMAND_H
#define _DESIGN_PATTERN_COMMAND_H
#include "Debug.h"
namespace DesignPattern_Command
{
    enum CmdEnum
    {
        orderDish = 0,
        placeOrder = 1,
        cook = 2,
        returnDish = 3,
        receiveDish = 4,
        makePayment = 5,
        placePayment = 6,
        processTransaction = 7,
        returnReceipt = 8,
        receiveReceipt = 9,
    };
    class Command //a Command is just an "invoke on a member function of an instance"
    {
        std::function<void()> m_invoke;
    public:
        explicit Command(std::function<void()> f) : m_invoke(f)
        {}
        void operator()() const { m_invoke(); }
    };
    class Person
    {
    protected:
        std::string m_name;
        std::unordered_map<CmdEnum, Command> m_cmd;
    public:
        explicit Person(const std::string & name):m_name(name), m_cmd(){}
        void AddCommand(CmdEnum c, const Command & cmd)
        {
            m_cmd.insert({c, cmd});
        }
        virtual ~Person() = 0;
        virtual void OrderDish(){}
        virtual void PlaceOrder(){}
        virtual void Cook(){}
        virtual void ReturnDish(){}
        virtual void ReceiveDish(){}
        virtual void MakePayment(){}
        virtual void PlacePayment(){}
        virtual void ProcessTransaction(){}
        virtual void ReturnReceipt(){}
        virtual void ReceiveReceipt(){}
    };
    Person::~Person(){}
    class Customer : public Person
    {
    public:
        Customer(const std::string & name):Person(name){}
        ~Customer(){}
        void OrderDish()
        {
            std::cout << m_name << "::OrderDish -> invoke Waiter::PlaceOrder" << std::endl;
            m_cmd.find(orderDish)->second();
        }
        void ReceiveDish()
        {
            std::cout << m_name << "::ReceiveDish" << std::endl;
        }
        void MakePayment()
        {
            std::cout << m_name << "::MakePayment -> invoke Waiter::PlacePayment" << std::endl;
            m_cmd.find(makePayment)->second();
        }
        void ReceiveReceipt()
        {
            std::cout << m_name << "::ReceiveReceipt" << std::endl;
        }
    };
    class Waiter : public Person
    {
    public:
        Waiter(const std::string & name):Person(name){}
        ~Waiter(){}
        void PlaceOrder()
        {
            std::cout << m_name << "::PlaceOrder -> invoke Chef::Cook" << std::endl;
            m_cmd.find(placeOrder)->second();
        }
        void PlacePayment()
        {
            std::cout << m_name << "::PlacePayment -> invoke Cashier::ProcessTransaction" << std::endl;
            m_cmd.find(placePayment)->second();
        }
        void ReturnDish()
        {
            std::cout << m_name << "::ReturnDish -> invoke Customer::ReceiveDish" << std::endl;
            m_cmd.find(returnDish)->second();
        }
        void ReturnReceipt()
        {
            std::cout << m_name << "::ReturnReceipt -> invoke Customer::ReceiveReceipt" << std::endl;
            m_cmd.find(returnReceipt)->second();
        }
    };
    class Chef : public Person
    {
    public:
        Chef(const std::string & name):Person(name){}
        ~Chef(){}
        void Cook()
        {
            std::cout << m_name << "::Cook -> invoke Waiter::ReturnDish" << std::endl;
            m_cmd.find(cook)->second();
        }
    };
    class Cashier : public Person
    {
    public:
        Cashier(const std::string & name):Person(name){}
        ~Cashier(){}
        void ProcessTransaction()
        {
            std::cout << m_name << "::ProcessTransaction -> invoke Waiter::ReturnReceipt" << std::endl;
            m_cmd.find(processTransaction)->second();
        }
    };

    void Test()
    {
        Person * customer = new Customer("Customer");
        Person * waiter = new Waiter("Waiter");
        Person * chef = new Chef("Chef");
        Person * cashier = new Cashier("Cashier");


        customer->AddCommand(orderDish, Command(std::bind(&Person::PlaceOrder, waiter)));
        customer->AddCommand(makePayment, Command(std::bind(&Person::PlacePayment, waiter)));

        waiter->AddCommand(placeOrder, Command(std::bind(&Person::Cook, chef)));
        waiter->AddCommand(returnDish, Command(std::bind(&Person::ReceiveDish, customer)));
        waiter->AddCommand(placePayment, Command(std::bind(&Person::ProcessTransaction, cashier)));
        waiter->AddCommand(returnReceipt, Command(std::bind(&Person::ReceiveReceipt, customer)));

        chef->AddCommand(cook, Command(std::bind(&Person::ReturnDish, waiter)));

        cashier->AddCommand(processTransaction, Command(std::bind(&Person::ReturnReceipt, waiter)));


        //1. customer orders dish to waiter
        customer->OrderDish();
        //2. customer makes payment to waiter
        customer->MakePayment();


        delete customer;
        delete waiter;
        delete chef;
        delete cashier;
    }
}
/*
Customer::OrderDish -> invoke Waiter::PlaceOrder
Waiter::PlaceOrder -> invoke Chef::Cook
Chef::Cook -> invoke Waiter::ReturnDish
Waiter::ReturnDish -> invoke Customer::ReceiveDish
Customer::ReceiveDish
Customer::MakePayment -> invoke Waiter::PlacePayment
Waiter::PlacePayment -> invoke Cashier::ProcessTransaction
Cashier::ProcessTransaction -> invoke Waiter::ReturnReceipt
Waiter::ReturnReceipt -> invoke Customer::ReceiveReceipt
Customer::ReceiveReceipt
 */
#endif

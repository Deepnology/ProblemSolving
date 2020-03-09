#ifndef _DESIGN_PATTERN_STRATEGY_H
#define _DESIGN_PATTERN_STRATEGY_H
#include "Debug.h"
namespace DesignPattern_Strategy
{
    class StrategyBase
    {
        virtual void ExecuteConcreteStrategy() = 0;
    public:
        void Execute()
        {
            ExecuteConcreteStrategy();
        };
        virtual ~StrategyBase() = 0;
    };
    StrategyBase::~StrategyBase() {}

    class StrategyDerived1 : public StrategyBase
    {
        void ExecuteConcreteStrategy(){ std::cout << "StrategyDerived1" << std::endl; }
        ~StrategyDerived1(){}
    };
    class StrategyDerived2 : public StrategyBase
    {
        void ExecuteConcreteStrategy(){ std::cout << "StrategyDerived2" << std::endl; }
        ~StrategyDerived2(){}
    };
    class StrategyDerived3 : public StrategyBase
    {
        void ExecuteConcreteStrategy(){ std::cout << "StrategyDerived3" << std::endl; }
        ~StrategyDerived3(){}
    };

    class Client
    {
        StrategyBase * m_strategy;
    public:
        void SetStrategy(int i)
        {
            if (i < 0)
                m_strategy = new StrategyDerived1;
            else if (i == 0)
                m_strategy = new StrategyDerived2;
            else
                m_strategy = new StrategyDerived3;
        }
        void Execute()
        {
            m_strategy->Execute();
        }
    };

    void Test()
    {
        Client c;
        c.SetStrategy(-1);
        c.Execute();
        c.SetStrategy(0);
        c.Execute();
        c.SetStrategy(1);
        c.Execute();
    }
}
/*
StrategyDerived1
StrategyDerived2
StrategyDerived3
 */
#endif

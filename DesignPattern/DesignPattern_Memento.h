#ifndef _DESIGN_PATTERN_MEMENTO_H
#define _DESIGN_PATTERN_MEMENTO_H
#include "Debug.h"
namespace DesignPattern_Memento
{
    class Memento
    {
        std::string m_state;
    public:
        explicit Memento(const std::string & state):m_state(state){}
        std::string GetState()
        {
            return m_state;
        }
    };
    class State
    {
        std::string m_state;
    public:
        explicit State(const std::string & state):m_state(state)
        {
            std::cout << "Ctor: " << m_state << std::endl;
        }
        std::string Get()
        {
            return m_state;
        }
        void Set(const std::string & state)
        {
            m_state = state;
            std::cout << "Set: " << m_state << std::endl;
        }
        Memento * SaveToMemento()
        {
            std::cout << "Save: " << m_state << std::endl;
            return new Memento(m_state);
        }
        void RestoreFromMemento(Memento * memento)
        {
            m_state = memento->GetState();
            std::cout << "Restore: " << m_state << std::endl;
        }
    };
    class StateRecords
    {
        std::vector<Memento *> m_records;
    public:
        StateRecords(){}
        void AddMemento(Memento * memento)
        {
            m_records.push_back(memento);
        }
        Memento * GetMemento(int index)
        {
            return m_records[index];
        }
    };

    void Test()
    {
        StateRecords r;
        State s("State0");
        r.AddMemento(s.SaveToMemento());
        s.Set("State1");
        r.AddMemento(s.SaveToMemento());
        s.Set("State2");
        s.Set("State3");
        s.RestoreFromMemento(r.GetMemento(1));
        s.RestoreFromMemento(r.GetMemento(0));
    }
}
#endif

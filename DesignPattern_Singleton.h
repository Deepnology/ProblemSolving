#ifndef _DESIGN_PATTERN_SINGLETON_H
#define _DESIGN_PATTERN_SINGLETON_H
#include "Debug.h"
namespace DesignPattern_Singleton
{
    class Singleton
    {
        static std::unique_ptr<Singleton> m_instance;
        static std::once_flag m_flag;
        //Singleton() { std::cout << "Singleton::Ctor" << std::endl; }
        Singleton() = default;
        Singleton(const Singleton &) = delete;
        Singleton(const Singleton &&) = delete;
        Singleton & operator=(const Singleton &) = delete;
        Singleton & operator=(const Singleton &&) = delete;
    public:
        static Singleton & Instance()
        {
            std::call_once(m_flag, []
            {
                m_instance.reset(new Singleton);
            });
            return *m_instance.get();
        }
        //~Singleton() { std::cout << "Singleton::Dtor" << std::endl; }
        ~Singleton() = default;
    };
    std::unique_ptr<Singleton> Singleton::m_instance;
    std::once_flag Singleton::m_flag;


    void Test()
    {
        Singleton::Instance();
        Singleton::Instance();
        Singleton::Instance();
        Singleton::Instance();
    }
}
#endif

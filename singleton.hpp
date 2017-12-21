#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_

#include <boost/utility.hpp>
#include <boost/thread/once.hpp>
#include <boost/scoped_ptr.hpp>

// Warning: If T's constructor throws, instance() will return a null reference.

template<class T>
class singleton : private boost::noncopyable
{
public:
    static T & instance()
    {
        boost::call_once(init, flag);
        return *t;
    }
private:
    static void init() // never throws
    {
        t.reset(new T());
    }
protected:
    ~singleton() {}
     singleton() {}
private:
     static boost::scoped_ptr<T> t;
     static boost::once_flag flag;
};
template<class T> boost::scoped_ptr<T> singleton<T>::t(0);
template<class T> boost::once_flag singleton<T>::flag = BOOST_ONCE_INIT;
/*
class static data member has external linkage, as well as global non-const non-static variables.
non-template class static data member must be defined in each source file (translation unit) that included the header file to avoid re-definition linking error,
but template class static data member don't have this issue.
it is because the definition of the template class static data member outside the class is itself a template definition.
http://stackoverflow.com/questions/1553854/template-static-variable
*/

#endif


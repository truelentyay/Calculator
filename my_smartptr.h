#ifndef MY_SMARTPTR_H
#define MY_SMARTPTR_H
#include <cstddef>


template <class T>
class SmartPtr
{
public:
    SmartPtr(T *ptr)
       : m_ptr(ptr)
    {

    }
    ~SmartPtr()
    {
       delete m_ptr;
       m_ptr = NULL;
    }

    T* operator->()
    {
       return m_ptr;
    }

    bool operator==(T* other)
    {
       return m_ptr == other;
    }
    bool isValid()
    {
       return NULL != m_ptr;
    }
    void reset(T* ptr)
    {
       m_ptr = ptr;
    }

private:
    SmartPtr(const SmartPtr&);
    SmartPtr operator=(const SmartPtr&);

    T *m_ptr;
};

#endif // MY_SMARTPTR_H

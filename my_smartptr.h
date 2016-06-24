#ifndef MY_SMARTPTR_H
#define MY_SMARTPTR_H
#include <cstddef>
#include <iostream>

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
       if (NULL != m_ptr)
       {
          delete m_ptr;
          m_ptr = NULL;
       }
    }

    T* operator->()
    {
       return m_ptr;
    }

    bool operator==(SmartPtr<T> other)
    {
       return this->m_ptr == other.m_ptr;
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
    int counter;
};

#endif // MY_SMARTPTR_H

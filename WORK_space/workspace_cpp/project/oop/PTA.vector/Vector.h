#ifndef __VECTOR__
#define __VECTOR__

#include <iostream>
#include <string>
using namespace std;

template <class T>
class Vector {
public:
  Vector();                     // creates an empty vector
  Vector(int size);              // creates a vector for holding 'size' elements
  Vector(const Vector& r);       // the copy ctor
  ~Vector();                     // destructs the vector 
  T& operator[](int index);      // accesses the specified element without bounds checking
  T& at(int index);              // accesses the specified element, throws an exception of
                                 // type 'std::out_of_range' when index <0 or >=m_nSize
  int size() const;              // return the size of the container
  void push_back(const T& x);    // adds an element to the end 
  void clear();                  // clears the contents
  bool empty() const;            // checks whether the container is empty

private:
  void inflate();                // expand the storage of the container to a new capacity,
                                 // e.g. 2*m_nCapacity
  T *m_pElements;                // pointer to the dynamically allocated storage
  int m_nSize;                   // the number of elements in the container
  int m_nCapacity;               // the total number of elements that can be held in the
                                 // allocated storage
};

template <class T>
Vector<T>::Vector()
{
    m_nCapacity = 0 ;
    m_nSize = 0 ;
    m_pElements = new T ;
    cout<<"Vector()"<<endl;
}

template <class T>
Vector<T>::Vector(int size)
{
    m_nCapacity = size ;
    m_nSize = 0 ;
    m_pElements = new T[m_nCapacity] ;
    cout<<"Vector(int size):"<<endl;
}

template <class T>
Vector<T>::Vector(const Vector& r)
{
    m_nSize = r.m_nSize;
    m_nCapacity = r.m_nCapacity;
    m_pElements = new T[m_nCapacity] ;
    for(int i = 0 ; i < m_nSize ; i++)
    {
        m_pElements[i] = r.m_pElements[i];
    }
    cout<<"Vector(const Vector& r)"<<endl;
}

template <class T>
Vector<T>::~Vector()
{
    delete[] m_pElements;
    cout<<"~Vector()"<<endl;
}

template <class T>
T& Vector<T>::operator[](int index)
{
    return this -> m_pElements[index] ;
}

template <class T>
T& Vector<T>::at(int index)
{
    if(index >=m_nSize || index < 0)
    {
        cout<<"std::out_of_range"<<endl;
        cout<<"Now we will stop the process."<<endl;
        system("pause");
        exit(0);
    }
    return this -> m_pElements[index] ;
}

template <class T>
int Vector<T>::size() const
{
    return m_nSize;
}

template <class T>
void Vector<T>::clear()
{
    m_nSize = 0;
    m_nCapacity = 0 ;
    //delete[] m_pElements;
}

template <class T>
bool Vector<T>::empty() const
{
    return m_nSize == 0 ;
}

template <class T>
void Vector<T>::push_back(const T& x)
{
    if(m_nSize+1 > m_nCapacity)
    {
        inflate();
    }
    m_pElements[m_nSize] = x ;
    m_nSize ++ ;
}

template <class T>
void Vector<T>::inflate()
{
    if(m_nCapacity == 0)
    {
        m_nCapacity = 1 ;
    }
    else
    {
        m_nCapacity = m_nCapacity * 2 ;
    }
    T * temp = m_pElements ; 
    m_pElements = new T[m_nCapacity] ;
    for(int i = 0 ; i < m_nSize ;i++)
    {
        m_pElements[i] = temp[i] ;
    }
    delete[] temp ;
}
#endif
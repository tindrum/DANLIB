//
//  DANLIB.h
//
//  Created by Daniel Henderson on 2/11/14.
//  CSUF
//  CPSC 131 Section 02 - Data Structures
//  Prof. M. Ahmadnia
//  Spring 2014
//
//  Copyright (c) 2014 Deep Bondi.  The MIT License (MIT).
//

#ifndef __ONE__
#define __ONE__

#include <string>
#include <iostream>

using namespace std;

template <class T, int n>
class ONE
{
private: T a[n];
public:
    void ReadData();
    int Total();
    void Display();
    void Average( T sum,float& ave);
};

template <class T, int n>
void ONE<T, n> :: ReadData()
{
    for(int i=0; i<n; ++i)
    {
        cout << "Enter a number:"; cin << a[i];
    }
}

template <class T, int n>
int ONE<T,n>::Total()
{
    T total =0;
    for(int i=0; i<n; ++i)
        total += a[i];
    return total;
}
template <class T, int n>
void ONE<T,n> :: Display()
{
    for(int i=0; i<n; ++i)
        cout << a[i] << '\t';
    cout << endl;
}
template <class T, int n>
void ONE<T, n> :: Average( T sum,float& ave)
{
    ave= float(sum)/5;

}
#endif /* defined(__ONE__) */

#ifndef __STACK__
#define __STACK__


// Stack class
// Implements basic stack functions:
//   push
//   pop
//   isEmpty - user must test,
//             no fail mechanism
//             if pop when empty
//   isFull  - user must test
//   clearStack - only sets top pointer
//                to zero, does not free
//                any objects in stack.
//   max - returns maximum allowed items
//         for object. maxSize is initiallized
//         by Stack constructor,
//         so maxSize varies for each
//         instance.

template<class T, int maxSize>
class Stack {
private:
    T a[maxSize];
    int top;
public:
    void clearStack();
    bool isEmpty();
    bool isFull();
    void push(T item);
    int max();
    T pop();

};

template<class T, int maxSize>
bool Stack<T, maxSize>::isEmpty() {
    return static_cast<bool>(top == 0);
}

template<class T, int maxSize>
bool Stack<T, maxSize>::isFull() {
    return static_cast<bool>(top == maxSize);
}

template<class T, int maxSize>
T Stack<T, maxSize>::pop() {
    return a[--top];
}

template<class T, int maxSize>
void Stack<T,maxSize>::push(T item){
    a[top++] = item;
}

// TODO: Clear stack of memory-using objects
//       when clearing stack, or decrement
//       use counts if objects have them.
template<class T, int maxSize>
void Stack<T,maxSize>::clearStack(){
    top = 0;
}

template<class T, int maxSize>
int Stack<T, maxSize>::max() {
    return maxSize;
}



#endif /* defined(__STACK__) */


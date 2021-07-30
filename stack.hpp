/* 
Implements a simple templated stack using the templated LinkedList from class

DO NOT EDIT THE CLASS DECLARATION BELOW. You will not submit this file.
*/

#ifndef __STACK_H
#define __STACK_H

#include "template-linkedlist.hpp"
#include <iostream>
#include <iostream>

using namespace std;

template <class T>
class Stack
{
private:
  LinkedList<T> *stack;

public:
  Stack(); // Constructor -- should allocate the stack

  T &peek(); // Returns a reference to the topmost value without removing it

  void push(T val); //Add the value to the top of the stack
  T pop();          //Removes and returns the value on top of the stack. If stack is empty, throw StackEmpty

  bool empty(); //Checks if the stack is empty

  Stack(const Stack<T> &); //Copy constructor

  const Stack<T> &operator=(const Stack<T> &copy); // Copy assignment

  ~Stack(); // Destructor -- deallocate the stack
};

//Prints the stack -- you can use this to test your stack, but you
// won't use this when implementing CallStack
template <class T>
ostream &operator<<(ostream &out, Stack<T> &s)
{
  Stack<T> temp = s;

  while (!temp.empty())
  {
    out << temp.pop() << endl;
  }
  return out;
}

//An exception thrown when peek/pop is called with an empty stack
struct StackEmpty : public exception
{
  const char *what() const throw()
  {
    return "The stack is empty!";
  }
};

/* 
DO NOT EDIT ABOVE THIS LINE
*/

//HINT: None of the following functions should be more than a few lines long. Let the
//  LinkedList do all the work

template <class T>
Stack<T>::Stack()
{
  LinkedList<T>();
}

template <class T>
T &Stack<T>::peek()
{

  /* TO DO! */ //Add exception
  try
  {
    Node<T> *temp = stack->getTail();
    return temp->value();
  }
  catch (StackEmpty e)
  {
    cout << e.what() << endl;
  }
}

template <class T>
void Stack<T>::push(T val)
{
  stack->insert(val, stack->getTail());
}

template <class T>
T Stack<T>::pop()
{
  T a = stack->getTail()->value();
stack->remove(stack->getTail());

  try
  {
    stack->remove(stack->getTail());
    return stack->getTail()->value();
  }
  catch (StackEmpty e)
  {
    cout << e.what() << endl;
  }

  return a;
}

template <class T>
bool Stack<T>::empty()
{
  /* TO DO! */
  return stack->empty();
}

template <class T>
Stack<T>::Stack(const Stack<T> &copy)
{
  stack->LinkedList(copy);
}

template <class T>
const Stack<T> &Stack<T>::operator=(const Stack<T> &copy)
{
  /* TO DO! */
  stack->operator=(copy);
}

template <class T>
Stack<T>::~Stack()
{
  stack->~LinkedList();
}

#endif
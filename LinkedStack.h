//Header File: LinkedStack.h

#ifndef H_LinkedStack
#define H_LinkedStack

#include "stackADT.h"

//Definition of the node
template <class Type>
struct nodeType
{
    Type info;
    nodeType<Type> *link;
};

template <class Type>
class LinkedStack : public stackADT<Type>
{
  public:
    LinkedStack();
      //Default constructor
      //Postcondition: stackTop = nullptr;

    LinkedStack(const LinkedStack<Type>& otherStack);
      //Copy constructor

    ~LinkedStack();
      //Destructor
      //Postcondition: All the elements of the stack are
      //               removed from the stack.

    const LinkedStack<Type>& operator= (const LinkedStack<Type>&);
      //Overload the assignment operator.

    bool isEmptyStack() const;
      //Function to determine whether the stack is empty.
      //Postcondition: Returns true if the stack is empty;
      //               otherwise returns false.

    //bool isFullStack() const;     /// removed by J.Goldstein
      //Function to determine whether the stack is full.
      //Postcondition: Returns false.

    void initializeStack();
      //Function to initialize the stack to an empty state.
      //Postcondition: The stack elements are removed;
      //               stackTop = nullptr;

    void push(const Type& newItem);
      //Function to add newItem to the stack.
      //Precondition: The stack exists and is not full.
      //Postcondition: The stack is changed and newItem
      //               is added to the top of the stack.

    Type top() const;
      //Function to return the top element of the stack.
      //Precondition: The stack exists and is not empty.
      //Postcondition: If the stack is empty, the program
      //               terminates; otherwise, the top
      //               element of the stack is returned.

    void pop();
      //Function to remove the top element of the stack.
      //Precondition: The stack exists and is not empty.
      //Postcondition: The stack is changed and the top
      //               element is removed from the stack.

  private:
    nodeType<Type> *stackTop; //pointer to the stack

    void copyStack(const LinkedStack<Type>& otherStack);
      //Function to make a copy of otherStack.
      //Postcondition: A copy of otherStack is created and
      //               assigned to this stack.
};

#endif

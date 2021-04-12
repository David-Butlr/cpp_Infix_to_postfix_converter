// LinkedStack.cpp

#include "LinkedStack.h"

//Default constructor
template <class Type>
LinkedStack<Type>::LinkedStack()
{
    stackTop = nullptr;
}

//copy constructor
template <class Type>
LinkedStack<Type>::LinkedStack(const LinkedStack<Type>& otherStack)
{
    stackTop = nullptr;
    copyStack(otherStack);
}//end copy constructor

    //destructor
template <class Type>
LinkedStack<Type>::~LinkedStack()
{
    initializeStack();
}//end destructor

    //overloading the assignment operator
template <class Type>
const LinkedStack<Type>& LinkedStack<Type>::operator=
    			  (const LinkedStack<Type>& otherStack)
{
    if (this != &otherStack) //avoid self-copy
        copyStack(otherStack);

    return *this;
}//end operator=

template <class Type>
bool LinkedStack<Type>::isEmptyStack() const
{
    return(stackTop == nullptr);
} //end isEmptyStack

template <class Type>
void LinkedStack<Type>:: initializeStack()
{
    nodeType<Type> *temp; //pointer to delete the node

    while (stackTop != nullptr)  //while there are elements in
                              //the stack
    {
        temp = stackTop;    //set temp to point to the
                            //current node
        stackTop = stackTop->link;  //advance stackTop to the
                                    //next node
        delete temp;    //deallocate memory occupied by temp
    }
} //end initializeStack


template <class Type>
void LinkedStack<Type>::push(const Type& newElement)
{
    nodeType<Type> *newNode;  //pointer to create the new node

    newNode = new nodeType<Type>; //create the node

    newNode->info = newElement; //store newElement in the node
    newNode->link = stackTop; //insert newNode before stackTop
    stackTop = newNode;       //set stackTop to point to the
                              //top node
} //end push


//Function to return the top element of the stack.
//Precondition: The stack exists and is not empty.
//Postcondition: If the stack is empty, the program
//               terminates; otherwise, the top
//               element of the stack is returned.
template <class Type>
Type LinkedStack<Type>::top() const
{
    assert(stackTop != nullptr); //if stack is empty,
                              //terminate the program
    return stackTop->info;    //return the top element
}//end top


//Function to remove the top element of the stack.
//Precondition: The stack exists and is not empty.
//Postcondition: The stack is changed and the top
//               element is removed from the stack.
template <class Type>
void LinkedStack<Type>::pop()
{
    nodeType<Type> *temp;   //pointer to deallocate memory

    if (stackTop != nullptr)
    {
        temp = stackTop;  //set temp to point to the top node

        stackTop = stackTop->link;  //advance stackTop to the
                                    //next node
        delete temp;    //delete the top node
    }
    else
        cout << "Cannot remove from an empty stack." << endl;
}//end pop


//Function to make a copy of otherStack.
//Postcondition: A copy of otherStack is created and
//               assigned to this stack.
template <class Type>
void LinkedStack<Type>::copyStack(const LinkedStack<Type>& otherStack)
{
    nodeType<Type> *newNode, *current, *last;

    if (stackTop != nullptr) //if stack is nonempty, make it empty
        initializeStack();

    if (otherStack.stackTop == nullptr)
        stackTop = nullptr;
    else
    {
        current = otherStack.stackTop;  //set current to point
                                   //to the stack to be copied
        //copy the stackTop element of the stack
        stackTop = new nodeType<Type>;  //create the node

        stackTop->info = current->info; //copy the info
        stackTop->link = nullptr;  //set the link field of the
                                //node to nullptr
        last = stackTop;        //set last to point to the node
        current = current->link;    //set current to point to
                                    //the next node

        //copy the remaining stack
        while (current != nullptr)
        {
            newNode = new nodeType<Type>;
            newNode->info = current->info;
            newNode->link = nullptr;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }//end while
    }//end else
} //end copyStack

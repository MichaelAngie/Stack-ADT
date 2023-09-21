#ifndef CS2_STACK_HPP_
#define CS2_STACK_HPP_
////////////////////////////////////////////////////////////////////////////
//
// File: stack.hpp
//
// Programmer: Michael Angie
// Updated:    Fall 2021

#include <new>
#include "../string/string.hpp"
////////////////////////////////////////////////////////////////////////////
//           
template<typename T> 
class Node 
{
	public:						//is this right/required?
	Node();
	Node(T newData) {data = newData;}
	
	T data;
	Node<T>* next;

};


////////////////////////////////////////////////////////////////////////////
// CLASS INV:
//
//    
template <typename T>
class stack {
public:
              stack     () : tos(0) {};
              stack     (const stack<T>&);
              ~stack    ();
    void      swap      (stack<T>&);// point their pointers to what eachother was oointing at
    stack<T>& operator= (stack<T>); // copy and swap idiom
	bool      empty     () const;	// are there nodes in the stack?
	bool      full      () const;	// if node cant be made, new returns nullptr.  check if it does, return true
	T         top       () const { return tos -> data; };	// what is the data at the top of the stack?
	T         pop       ();			// return the data at the top of the stack and then delete the top node, and repoint *tos the the next in line
	void      push      (const T&);	// make a new node with the argument and add that to the top of the stack.

private:
	Node<T>   *tos;
};


//swap
template <typename T>
void stack<T>::swap(stack<T>& rhs)
{
	Node<T>* temp = tos;
	tos = rhs.tos;
	rhs.tos = temp;
}

//copy constru
template <typename T>
stack<T>::stack(const stack<T>& rhs) : stack()
{
	Node<T>* lhsTemp;
	Node<T>* rhsTemp = rhs.tos;

	while (rhsTemp != 0)
	{
		if (tos == 0)
		{
			tos = new Node<T>(rhs.tos->data);
			lhsTemp = tos;
			rhsTemp = rhs.tos->next;
		}
		
		if (rhsTemp != 0)
		{
			lhsTemp->next = new Node<T>(rhsTemp->data);
			lhsTemp = lhsTemp->next;
			rhsTemp = rhsTemp->next;
		}
	}
}

//assignment
template <typename T>
stack<T>& stack<T>::operator=(stack<T> rhs)
{
	swap(rhs);
	return *this;
}

//destru
template <typename T>
stack<T>::~stack()
{
	Node<T>* temp;

	while (tos != 0)
	{
		temp = tos;
		tos = tos->next;
		delete temp;
	}
}

//empty
template <typename T>
bool stack<T>::empty() const
{
	return (tos == 0);
}

//full
template <typename T>
bool stack<T>::full() const
{
	Node<T>* test = new Node<T>;

	if (test == 0) return true;
	else
	{
		delete test;
		return false;
	}
}

//pop
template <typename T>
T stack<T>::pop()
{
	Node<T>* temp = tos;
	T data = tos->data;
	tos = tos->next;
	delete temp;
	return data;
}

//push
template <typename T>
void stack<T>::push(const T& data)
{
	Node<T>* temp = tos;
	tos = new Node<T>(data);
	tos->next = temp;
}



#endif

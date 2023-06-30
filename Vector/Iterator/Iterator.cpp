#include "Iterator.hpp"

////////////////////////////////////////////// Constructors //////////////////////////////////////////////////////
template<class T>
inline Iterator<T>::Iterator() noexcept : m_Current(nullptr) {}

template<class T>
inline Iterator<T>::Iterator(T* ptr): m_Current(ptr){}

template<class T>
inline Iterator<T>::Iterator(const Iterator& it) noexcept : m_Current(it.m_Current)
{
	// default copy constuctor
	// peform a shallow copy (no block of memory to copy data from)
}

template<class T>
inline Iterator<T>::Iterator(Iterator&& it) noexcept: m_Current(nullptr)
{
	// move constructor (move pointer from it to this object
	// 1. make sure this->m_Current are empty == nullptr	(initialziation list look about)
	// 2. assign this->m_Current with it.m_Current
	// 3. update it.m_Current with nullptr (so as move be completed)
	this->m_Current = it.m_Current;
	it.m_Current = nullptr;
	
}


////////////////////////////////////////////// Assignment Operators (copy, move) //////////////////////////////////////////////////////
template<class T>
inline Iterator<T>& Iterator<T>::operator=(const Iterator<T>& it)
{
	// if both have same pointer return current else copy
	if(this != &it)
	{
		// peform copy
		this->m_Current = it.m_Current;
	}

	return *this;
}

template<class T>
inline Iterator<T>& Iterator<T>::operator=(Iterator<T>&& it)
{
	// if both points to same block of memory return *this, else move from it to this
	if (this != &it)
	{
		/*
		* 1. make sure current is empty 
		* 2. current = it.current
		* 3. it.current = nullptr
		*/

		this->m_Current = nullptr;
		this->m_Current = it.m_Current;
		it.m_Current = nullptr;
	}

	// any way *this
	return *this;
}


////////////////////////////////////////////// Destructor /////////////////////////////////////////////////////////////////////////////
template<class T>
inline Iterator<T>::~Iterator() noexcept{}


////////////////////////////////////////////// Setters And Getters (Encapsulation) //////////////////////////////////////////////////////
template<class T>
inline void Iterator<T>::setCurrentPointer(T* ptr)
{
	this->m_Current = ptr;
}

template<class T>
inline T* Iterator<T>::getCurrentPointer() const
{
	return this->m_Current;
}


/////////////////////////////////////////////// Operators Overloadings (Dereferencing, Arrow) /////////////////////////////////////////////////////////////////////////////
template<class T>
inline T& Iterator<T>::operator*() const
{
	return *m_Current;
}

template<class T>
inline T* Iterator<T>::operator->() const
{
	return m_Current;
}


////////////////////////////////////////////// Operators Overloadings (Pre-increment, post-increment) /////////////////////////////////////////////////////////////////////////////
template<class T>
inline Iterator<T>& Iterator<T>::operator++()
{
	// pre-increment operator
	// increment current and return the incremented iterator
	++m_Current;
	return *this;
}

template<class T>
inline Iterator<T> Iterator<T>::operator++(const int)
{
	// in postfix increment operator
	// returns the old current then increment
	Iterator<T> oldIterator(*this);	// store before incrmenting it
	++(*this);						// increment it

	return oldIterator;

}

////////////////////////////////////////////// Operators Overloadings (Pre-decrement, Post-decrement) /////////////////////////////////////////////////////////////////////////////
template<class T>
inline Iterator<T>& Iterator<T>::operator--()
{
	// pre decrement operator (decrement first then return this object)
	--m_Current;
	return *this;
}

template<class T>
inline Iterator<T>& Iterator<T>::operator--(int)
{
	// post decrement operator, store old current int tmp and decrement it finally return *this
	Iterator<T> oldIterator(*this);

	m_Current--;

	return oldIterator;
}

////////////////////////////////////////////// Operators Overloadings (Arithmatic operators) /////////////////////////////////////////////////////////////////////////////
template<class T>
inline Iterator<T>& Iterator<T>::operator+(difference_type n)
{
	this->m_Current += n;
	return *this;
}

template<class T>
inline Iterator<T> Iterator<T>::operator+(const Iterator<T>& it)
{
	return Iterator<T>(m_Current + it.m_Current);
}

template<class T>
inline Iterator<T>& Iterator<T>::operator-(difference_type n)
{
	this->m_Current -= n;
	return *this;
}

template<class T>
inline size_t Iterator<T>::operator-(const Iterator<T>& it)
{
	T* big = std::max(it.m_Current, m_Current);
	T* small = std::min(it.m_Current, m_Current);
	return static_cast<size_t>(big - small);
}




template<class T>
inline Iterator<T>& Iterator<T>::operator+=(difference_type n)
{
	// increment this object and return
	m_Current += n;
	return *this;
}

template<class T>
inline Iterator<T>& Iterator<T>::operator-=(difference_type n)
{
	// decrement this object and return
	m_Current -= n;
	return *this;
}

////////////////////////////////////////////// Operators Overloadings (comparison operators) /////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Iterator<T>::operator==(const Iterator<T>& it) const
{
	return this->m_Current == it.m_Current;
}

template<class T>
inline bool Iterator<T>::operator!=(const Iterator<T>& it) const
{
	return it.m_Current != this->m_Current;
}

//template<class T>
//inline bool Iterator<T>::operator!=(const Iterator& it) const
//{
//	return this->m_Current != it.m_Current;
//}
//
//template<class T>
//inline std::ostream& operator<<(std::ostream& output, const Iterator<T>& it)
//{
//	// print the memory address for the current ptr
//	output << it.m_Current << "\n";
//	return output;
//}

// template<class T>
// inline std::istream& operator>>(std::istream& input, Iterator<T>& it)
// {
// 	// take value from user
// 	T value;
// 	input >> value;

// 	// store it's memeory address in current
// 	it.m_Current = &value;

// 	return input;

// }
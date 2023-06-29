#pragma once
#include <initializer_list>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include "../Iterator/Iterator.hpp"

template<class T = int>
class Vector
{
	/* Iterators (Alias) */
public:
	using iterator = Iterator<T>;

	/* Instance Attributes */
private:
	T* m_Data;
	size_t m_Size;
	size_t m_Capacity;

	/* Rule of big 5 and instance methods */
public:
	explicit Vector();												// default constructor
	Vector(size_t size, const T& defaultValue=0);					// parametrized constructor
	explicit Vector(std::initializer_list<T> values);						// initialize from initializer list
	Vector(const Vector<T>& otherVector);							// default copy constructor ( deep copy )
	Vector(Vector<T>&&) noexcept;									// move constructor
	Vector<T>& operator=(const Vector<T>&) noexcept;				// copy assignment operator
	Vector<T>&& operator=(const Vector<T>&&);						// move assignment operator
	~Vector() noexcept;														// destructor

	// Capacity, Size
	size_t size() const;
	size_t capacity() const;
	size_t Max_Size() const;
	bool Empty() const;
	bool Full() const;
	void Reserve(size_t newCapacity);
	void Shrink_To_Fit();
	

	// Modifiers
	const T& Push_Back(const T& element);
	void Push_Back(T&& element);
	T Pop_Back();
	void Resize(size_t newSize);
	void Resize(size_t newSize, const T& defaultValue);
	void Swap(Vector<T>& v);
	void Clear();

	// Modifiers based iterators
	T Erase(const size_t& index);
	void Erase(iterator pos);
	void Erase(iterator first, iterator end);

	const T& Insert(const size_t& index, const T& element);
	void Insert(iterator pos, const T& element);
	void Insert(iterator startPos, std::initializer_list<T> elements);

	// Element access
	const T& At(size_t index) const;
	T& At(size_t index);
	T& Back();
	const T& Back() const;
	T& Front();
	const T& Front() const;
	T* Data();
	const T* Data() const;

	
	



	// Operators overloadings
	const T& operator[](size_t index) const;						// supscriping operator ( return const: can't modify any values in vector)
	T& operator[](size_t index);									// supscipting operator ( return reference to element: able to modify element in vector)

	bool operator<(const Vector<T>& otherVector) const;				// smaller opeartor	(Comparison  operator)
	bool operator>(const Vector<T>& otherVector) const;				// greater operator (Comparison  operator)
	bool operator==(const Vector<T>& otherVector) const;				// equality operator (Comparison  opeartor)
	bool operator<=(const Vector<T>& otherVector) const;				// smaller or equal operator (comaprison operator)
	bool operator>=(const Vector<T>& otherVector) const;				// greater or equal operator (comparison operator)
	bool operator!=(const Vector<T>& otherVector) const;				// inequality operator (comparison operator)

	Vector<T> operator+(const Vector<T>& otherVector) const;
	Vector<T> operator+(const T& scalar) const;
	Vector<T> operator-(const Vector<T>& otherVector) const;
	Vector<T> operator-(const T& scalar) const;
	Vector<T> operator*(const Vector<T>& otherVector) const;			// implements wise
	Vector<T> operator*(const T& scalar) const;							// implements scaler logic
	Vector<T> operator/(const Vector<T>& otherVector) const;
	Vector<T> operator/(const T& scalar) const;
	

	// Friends
	//friend ostream& operator<<(ostream& output, const Vector& v);
	//friend istream& operator>>(istream& input, Vector& v);

	/* Iterators */
	iterator begin();
	iterator end();

	/* Helper Methods */
private:
	void ReAlloc(const size_t newCapacity);
	void ReAlloc(const size_t newCapacity, const T& defaultValue);
};


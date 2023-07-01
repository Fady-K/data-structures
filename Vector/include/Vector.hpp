/**
 * @file Vector.hpp
 * @author Fady Kamal (popfadykamal151617@gmail.com)
 * @brief This the header file of Vector class.
 * @details It contains all Vector members.
 * @version 0.1
 * @date 2023-07-01
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <initializer_list>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include "../Iterator/Iterator.hpp"
#include "../exceptions/VectorException.hpp"

/**
 * @class Vector
 * @brief A dynamic array that provides functionality similar to the standard vector container in stl.
 * 
 * @tparam T The type of elements stored in the vector, default type (int)
 */
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
	/**
	 * @brief Default constructor. Constructs an empty vector with zero size and capacity of 1.
	 * @details Added explicit to add to force the compiler not to ignore with original vector in stl
	 */
	explicit Vector();												// default constructor


	/**
	 * @brief Parametrized constructor. Constructs a vector with the specified size and default value.
	 * @param size The size of the constructed vector.
	 * @param defaultValue The default value to initialize the elements with, if int = 0.
	 */
	Vector(size_t size, const T& defaultValue=0);					// parametrized constructor

	/**
	 * @brief Constructor that initializes the vector with the elements from given initializer list.
	 * @param values The initializer list containing the elements to be copied to the vector (deep copy).
	 */
	explicit Vector(std::initializer_list<T> values);				// initialize from initializer list

	/**
	 * @brief Copy constructor. Constructs a vector by deep copying the elements from another vector.
	 * @details It performs deep copy where a new block of memory is registered and elements get copied from other
	 * vector to *this using std::copy().
	 * @param otherVector The vector to be copied.
	 */
	Vector(const Vector<T>& otherVector);							// default copy constructor ( deep copy )

	/**
	 * @brief Move constructor. Constructs a vector by moving the resources from another vector.
	 * @param otherVector The vector to be moved.
	 */
	Vector(Vector<T>&&) noexcept;									// move constructor

	/**
	 * @brief Copy assignment operator. Assigns the elements from another vector to this vector by deep copying.
	 * @param otherVector The vector to be copied.
	 * @return A reference to the updated vector.
	 */
	Vector<T>& operator=(const Vector<T>&) noexcept;				// copy assignment operator

	/**
	 * @brief Move assignment operator. Moves the resources from another vector to this vector.
	 * @param otherVector The vector to be moved.
	 * @return A reference to the updated vector.
	 */
	Vector<T>& operator=(Vector<T>&&);								// move assignment operator

	/**
	 * @brief Destructor. Deallocates the dynamically allocated memory of the vector.
	 * @details In addition to deallocation the memroy, it sets m_Size and Capacity = 0.
	 */
	~Vector() noexcept;												// destructor


	// Capacity, Size

	/**
	 * @brief Returns number of elements in the vector.
	 * @return size_t Number of elements in the vector
	 */
	size_t size() const;

	/**
	 * @brief Returns number of objects this vector can store in the current reserved block of memeory.
	 * 
	 * @return size_t Number of objects vector can store within the current reserved block of memory.
	 */
	size_t capacity() const;

	/**
	 * @brief Returns the maximum size this vector can reach in terms of computer resources (Theoratically).
	 * @details 
	 * @return size_t Max size this vector can reach in terms of computer reserouces.
	 */
	size_t Max_Size() const;

	/**
	 * @brief Checks if the vector is empty.
	 * 
	 * @return true If vector is empty.
	 * @return false If vector is !empty.
	 */
	bool Empty() const;

	/**
	 * @brief Check whether (current allocated block of memory) is full or not.
	 * @details (size >= capacity)
	 * @return true If current allocated block of memory is full.
	 * @return false If current allocated block of memory isn't full.
	 */
	bool Full() const;

	/**
	 * @brief Reserves memory for a specified capacity.
	 * @param newCapacity The new capacity to reserve.
	 * @details If the specified capacity is greater than the current capacity of the vector:
	 * - Allocate a new memory block with the specified capacity.
	 * - If there are elements in the vector:
	 * - Perform deep Copy to the elements from the existing memory block to the new block.
	 * - Deallocate the old memory block.
	 * - Update the vector's capacity to the specified capacity.
	 * - Else (newCapcity <= currentCapacity):
	 * - Do nothing.
	 * 
	 */
	void Reserve(size_t newCapacity);

	/**
	 * @brief Reduces the capacity of the vector to match its size (Shrinks vector capacity till it fits the size).
	 * @details Creates a new memory block with a size equal to the current size of the vector.
	 * - Copy the elements from the existing memory block to the new block.
	 * - Deallocate the old memory block.
	 * - Set the vector's capacity to match its size.
	 */
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
	const T& operator[](size_t index) const;							// supscriping operator ( return const: can't modify any values in vector)
	T& operator[](size_t index);										// supscipting operator ( return reference to element: able to modify element in vector)

	bool operator<(const Vector<T>& otherVector) const;					// smaller opeartor	(Comparison  operator)
	bool operator>(const Vector<T>& otherVector) const;					// greater operator (Comparison  operator)
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


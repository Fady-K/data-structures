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
	Vector(size_t size, const T& defaultValue = 0);					// parametrized constructor

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
	/**
	 * @brief Adds an element to the end of the vector.
	 * @param element The element to be added.
	 * @return Constant reference to the added element (can't be modified).
	 * @details This function adds an element to the end of the vector. If the vector's capacity is not sufficient to accommodate the new element, the vector's capacity will be increased accordingly.
	 * The added element will be copied from the provided value.
	 * @note The function may invalidate any existing references or iterators to the vector elements.
	 *
	 * @note The time complexity of this function is o(1) and (n) incase it will resize the vector.
	 */
	const T& Push_Back(const T& element);

	/**
	 * @brief Adds an element to the end of the vector by moving it.
	 * @param element The element to be added.
	 * @details This function adds an element to the end of the vector by moving it. If the vector's capacity is not sufficient to accommodate the new element, the vector's capacity will be increased accordingly.
	 * The added element will be moved from the provided value.
	 * @note The function may invalidate any existing references or iterators to the vector elements.
	 *
	 * @note The time complexity of this function is o(1) and (n) incase it will resize the vector.
	 */
	void Push_Back(T&& element);

	/**
	 * @brief Removes and returns the last element of the vector.
	 * @return The last element of the vector.
	 * @details This function removes and returns the last element of the vector. The size of the vector is reduced by one.
	 * If the vector is empty before calling this function, the behavior is undefined.
	 * @note The function may invalidate any existing references or iterators to the vector elements.
	 *
	 * @note The time complexity of this function is O(1).
	 */
	T Pop_Back();

	/**
	 * @brief Resizes the vector to a new size.
	 * @param newSize The new size of the vector.
	 * @details This function changes the size of the vector to the specified new size.
	 * If the new size is smaller than the current size, elements at the end of the vector are removed.
	 * If the new size is larger than the current size, additional elements are appended to the vector, and their values are default-initialized.
	 * @note The function may invalidate any existing references or iterators to the vector elements.
	 *
	 * @note The time complexity of this function is O(newSize) in the worst case.
	 */
	void Resize(size_t newSize);

	/**
	 * @brief Resizes the vector to a new size and assigns a default value to the new elements.
	 * @param newSize The new size of the vector.
	 * @param defaultValue The default value to be assigned to the new elements.
	 * @details This function changes the size of the vector to the specified new size.
	 * If the new size is smaller than the current size, elements at the end of the vector are removed.
	 * If the new size is larger than the current size, additional elements are appended to the vector, and their values are set to the provided default value.
	 * @note The function may invalidate any existing references or iterators to the vector elements.
	 *
	 * @note The time complexity of this function is O(newSize) in the worst case.
	 */
	void Resize(size_t newSize, const T& defaultValue);

	/**
	 * @brief Swaps the contents of this vector with another vector.
	 * @param v The vector to swap with.
	 * @details This function swaps the elements of this vector with another vector. After the swap, this vector will contain the elements of the other vector, and the other vector will contain the elements of this vector.
	 * The operation does not involve the reallocation of memory.
	 * @note The function may invalidate any existing references or iterators to the vector elements.
	 *
	 * @note The time complexity of this function is O(1) Thanks to std::swap().
	 */
	void Swap(Vector<T>& v);

	/**
	 * @brief Clears the vector.
	 * @details This function removes all elements from the vector by calling each destructor, leaving it with a size of 0.
	 * The function do nothing to the memory block used by the vector, meaning capacity stays the same.
	 * @note The function may invalidate any existing references or iterators to the vector elements.
	 * @note The time complexity of this function is O(n).
	 * @note To deallocate the extra memeory, you can use shrink_to_fit().
	 */
	void Clear();


	// Modifiers based iterators
	/**
	 * @brief Erases the element at the specified index from the vector.
	 * @param index The index of the element to erase.
	 * @details It takes index where element exists and erase it by shifting all elements to left direction (v[i] = v[i + 1]), which overrides that element.
	 * @return A copy of the erased element.
	 * @note The function may invalidate any existing references or iterators to the vector elements.
	 * @note The time complexity of this operation is linear O(n), where n is the size of the vector as shift all .
	 */
	T Erase(const size_t& index);

	/**
	 * @brief Erases the element pointed to by the iterator.
	 * @param pos An iterator pointing to the element to erase.
	 * @details It shifts all elements after the given position to the left side, causing element in this position to get overriden.
	 * @note The function may invalidate the iterator and any existing references to the vector elements.
	 * @note The time complexity of this operation is linear O(n), where n is the size of the vector.
	 */
	void Erase(iterator pos);

	/**
	 * @brief Erases a range of elements specified by the iterator range [first, last).
	 * @param first An iterator pointing to the first element of the range.
	 * @param last An iterator pointing to the element after the last element of the range.
	 * @note The function may invalidate the iterators and any existing references to the vector elements within the range.
	 * @note The time complexity of this operation is linear O(n), where n is the size of the vector as shift all elemnts after this position to the left direction causing element in this position to get overriden.
	 */
	void Erase(iterator first, iterator end);

	/**
	 * @brief Inserts an element at the specified index in the vector.
	 * @param index The index at which the element will be inserted.
	 * @param element The element to be inserted.
	 * @return A reference to the inserted element.
	 * @note The function may invalidate any existing references or iterators to the vector elements.
	 * @note The time complexity of this operation is linear O(n), where n is the size of the vector.
	 */
	const T& Insert(const size_t& index, const T& element);

	/**
	 * @brief Inserts an element at the specified position in the vector.
	 * @param pos An iterator pointing to the position at which the element will be inserted.
	 * @param element The element to be inserted.
	 * @note The function may invalidate any existing references or iterators to the vector elements.
	 * @note The time complexity of this operation is linear O(n), where n is the size of the vector.
	 */
	void Insert(iterator pos, const T& element);

	/**
	 * @brief Inserts multiple elements from an initializer list at the specified position in the vector.
	 * @param pos An iterator pointing to the position at which the elements will be inserted.
	 * @param elements The initializer list of elements to be inserted.
	 * @note The function may invalidate any existing references or iterators to the vector elements.
	 * @note The time complexity of this operation is linear O(n), where n is the size of the vector.
	 */
	void Insert(iterator startPos, std::initializer_list<T> elements);


	// Element access
	/**
	 * @brief Accesses the element at the specified index in the vector.
	 * @param index The index of the element to access.
	 * @return A reference to the element at the specified index.
	 * @note The function performs bound checking and throws an exception if the index is out of range.
	 */
	const T& At(size_t index) const;

	/**
	 * @brief Accesses the element at the specified index in the vector.
	 * @param index The index of the element to access.
	 * @return A reference to the element at the specified index.
	 * @note The function performs bound checking and throws an exception if the index is out of range.
	 */
	T& At(size_t index);

	/**
	 * @brief Returns a reference to the last element in the vector.
	 * @return A reference to the last element in the vector.
	 * @note The function performs bound checking and throws an exception if the vector is empty.
	 */
	T& Back();

	/**
	 * @brief Returns a reference to the last element in the vector.
	 * @return A reference to the last element in the vector.
	 * @note The function performs bound checking and throws an exception if the vector is empty.
	 */
	const T& Back() const;

	/**
	 * @brief Returns a reference to the first element in the vector.
	 * @return A reference to the first element in the vector.
	 * @note The function performs bound checking and throws an exception if the vector is empty.
	 */
	T& Front();

	/**
	 * @brief Returns a reference to the first element in the vector.
	 * @return A reference to the first element in the vector.
	 * @note The function performs bound checking and throws an exception if the vector is empty.
	 */
	const T& Front() const;

	/**
	 * @brief Returns a pointer to the underlying array of the vector.
	 * @return A pointer to the underlying array of the vector.
	 */
	T* Data();

	/**
	 * @brief Returns a pointer to the underlying array of the vector.
	 * @return A pointer to the underlying array of the vector.
	 */
	const T* Data() const;



	// Operators overloadings
	/**
	 * @brief Returns a const reference to the element at the specified index in the vector.
	 * @param index The index of the element to access.
	 * @return A const reference to the element at the specified index.
	 * @throws VectorException if the index is out of range.
	 *
	 * The subscripting operator allows accessing the elements of the vector using array-like syntax.
	 * This version of the operator returns a const reference, which means that the element cannot be modified.
	 * If the specified index is out of range (i.e., less than 0 or greater than or equal to the size of the vector),
	 * a VectorException is thrown.
	 */
	const T& operator[](size_t index) const;	

	/**
	 * @brief Returns a reference to the element at the specified index in the vector.
	 * @param index The index of the element to access.
	 * @return A reference to the element at the specified index.
	 * @throws VectorException if the index is out of range.
	 *
	 * The subscripting operator allows accessing the elements of the vector using array-like syntax.
	 * This version of the operator returns a reference, which allows modifying the element in the vector.
	 * If the specified index is out of range (i.e., less than 0 or greater than or equal to the size of the vector),
	 * a VectorException is thrown.
	 */			
	T& operator[](size_t index);		


	/**
	 * @brief Checks if the vector is lexicographically smaller than the otherVector.
	 * @param otherVector The vector to compare against.
	 * @return True if the vector is lexicographically smaller than the otherVector, false otherwise.
	 *
	 * The smaller operator compares the vector with the otherVector in a lexicographical manner.
	 * The size of the vectors is compared first. If the sizes are not equal, the vector with a smaller size is considered smaller.
	 * If the sizes are equal, the elements of the vectors are compared element by element until a pair of elements that are not equal is found.
	 * If an element in the vector is less than the corresponding element in the otherVector, the vector is considered smaller.
	 * If all elements are equal, the vectors are considered equal and false is returned.
	 */
	bool operator<(const Vector<T>& otherVector) const;		

	/**
	 * @brief Checks if the vector is lexicographically greater than the otherVector.
	 * @param otherVector The vector to compare against.
	 * @return True if the vector is lexicographically greater than the otherVector, false otherwise.
	 *
	 * The greater operator compares the vector with the otherVector in a lexicographical manner.
	 * The size of the vectors is compared first. If the sizes are not equal, the vector with a larger size is considered greater.
	 * If the sizes are equal, the elements of the vectors are compared element by element until a pair of elements that are not equal is found.
	 * If an element in the vector is greater than the corresponding element in the otherVector, the vector is considered greater.
	 * If all elements are equal, the vectors are considered equal and false is returned.
	 */
	bool operator>(const Vector<T>& otherVector) const;	

	/**
	 * @brief Checks if the vector is equal to the otherVector.
	 * @param otherVector The vector to compare against.
	 * @return True if the vector is equal to the otherVector, false otherwise.
	 *
	 * The equality operator checks if the vector is equal to the otherVector.
	 * The size of the vectors is compared first. If the sizes are not equal, the vectors are considered unequal and false is returned.
	 * If the sizes are equal, the elements of the vectors are compared element by element.
	 * If any pair of elements is not equal, the vectors are considered unequal and false is returned.
	 * If all elements are equal, the vectors are considered equal and true is returned.
	 */
	bool operator==(const Vector<T>& otherVector) const;

	/**
	 * @brief Checks if the vector is lexicographically smaller than or equal to the otherVector.
	 * @param otherVector The vector to compare against.
	 * @return True if the vector is lexicographically smaller than or equal to the otherVector, false otherwise.
	 *
	 * The smaller or equal operator checks if the vector is lexicographically smaller than the otherVector or equal to it.
	 * It uses the less than operator and the equality operator internally to perform the comparison.
	 */
	bool operator<=(const Vector<T>& otherVector) const;	

	/**
	 * @brief Checks if the vector is lexicographically greater than or equal to the otherVector.
	 * @param otherVector The vector to compare against.
	 * @return True if the vector is lexicographically greater than or equal to the otherVector, false otherwise.
	 *
	 * The greater or equal operator checks if the vector is lexicographically greater than the otherVector or equal to it.
	 * It uses the greater than operator and the equality operator internally to perform the comparison.
	 */			
	bool operator>=(const Vector<T>& otherVector) const;	

	/**
	 * @brief Checks if the vector is not equal to the otherVector.
	 * @param otherVector The vector to compare against.
	 * @return True if the vector is not equal to the otherVector, false otherwise.
	 *
	 * The inequality operator checks if the vector is not equal to the otherVector.
	 * It uses the equality operator internally to perform the comparison and returns the negation of the result.
	 */			
	bool operator!=(const Vector<T>& otherVector) const;				


	/**
	 * @brief Overloads the addition operator to perform element-wise addition of two vectors.
	 *
	 * @param otherVector The vector to be added.
	 * @return A new vector that contains the sum of corresponding elements.
	 *
	 * This operator performs element-wise addition of two vectors. It creates a new vector where each element is the sum of the corresponding elements from the operands.
	 */
	Vector<T> operator+(const Vector<T>& otherVector) const;

	/**
	 * @brief Overloads the addition operator to perform scalar addition with a vector.
	 *
	 * @param scalar The scalar value to be added.
	 * @return A new vector that contains the result of adding the scalar to each element.
	 *
	 * This operator performs scalar addition with a vector. It creates a new vector where each element is the original element incremented by the scalar value.
	 */
	Vector<T> operator+(const T& scalar) const;

	/**
	 * @brief Overloads the subtraction operator to perform scalar subtraction from a vector.
	 *
	 * @param scalar The scalar value to be subtracted.
	 * @return A new vector that contains the result of subtracting the scalar from each element.
	 *
	 * This operator performs scalar subtraction from a vector. It creates a new vector where each element is the original element decremented by the scalar value.
	 */
	Vector<T> operator-(const Vector<T>& otherVector) const;

	/**
	 * @brief Overloads the subtraction operator to perform scalar subtraction from a vector.
	 *
	 * @param scalar The scalar value to be subtracted.
	 * @return A new vector that contains the result of subtracting the scalar from each element.
	 *
	 * This operator performs scalar subtraction from a vector. It creates a new vector where each element is the original element decremented by the scalar value.
	 */
	Vector<T> operator-(const T& scalar) const;

	/**
	 * @brief Overloads the multiplication operator to perform scalar multiplication with a vector.
	 *
	 * @param scalar The scalar value to be multiplied.
	 * @return A new vector that contains the result of multiplying each element by the scalar.
	 *
	 * This operator performs scalar multiplication with a vector. It creates a new vector where each element is the original element multiplied by the scalar value.
	 */
	Vector<T> operator*(const Vector<T>& otherVector) const;		

	/**
	 * @brief Overloads the multiplication operator to perform scalar multiplication with a vector.
	 *
	 * @param scalar The scalar value to be multiplied.
	 * @return A new vector that contains the result of multiplying each element by the scalar.
	 *
	 * This operator performs scalar multiplication with a vector. It creates a new vector where each element is the original element multiplied by the scalar value.
	 */
	Vector<T> operator*(const T& scalar) const;							

	/**
	 * @brief Overloads the division operator to perform element-wise division of two vectors.
	 *
	 * @param otherVector The vector to be divided.
	 * @return A new vector that contains the result of dividing each element by the corresponding element in the other vector.
	 * @throw VectorException if the sizes of the vectors are not equal.
	 *
	 * This operator performs element-wise division of two vectors. It creates a new vector where each element is the quotient of dividing the corresponding elements from the operands. If the sizes of the vectors are not equal, a VectorException is thrown.
	 */
	Vector<T> operator/(const Vector<T>& otherVector) const;

	/**
	 * @brief Overloads the division operator to perform scalar division with a vector.
	 *
	 * @param scalar The scalar value to be divided by.
	 * @return A new vector that contains the result of dividing each element by the scalar.
	 *
	 * This operator performs scalar division with a vector. It creates a new vector where each element is the original element divided by the scalar value.
	 */
	Vector<T> operator/(const T& scalar) const;


	// Friends
	//friend ostream& operator<<(ostream& output, const Vector& v);
	//friend istream& operator>>(istream& input, Vector& v);


	// Iterators
	/**
	 * @brief Returns an iterator pointing to the first element in the vector.
	 * @return An iterator pointing to the first element in the vector.
	 */
	iterator begin();

	/**
	 * @brief Returns an iterator pointing to the past-the-end element in the vector.
	 * @return An iterator pointing to the past-the-end element in the vector.
	 */
	iterator end();

	/* Helper Methods */
private:
	/**
	 * @brief Reallocates memory for the vector with the specified new capacity.
	 * @param newCapacity The new capacity for the vector.
	 *
	 * If the new capacity is less than or equal to the current capacity, no reallocation is performed.
	 * Instead, the size of the vector is adjusted to match the new capacity.
	 * If the new capacity is greater than the current capacity, a new block of memory is allocated
	 * and the elements from the old block are moved to the new block.
	 * The old memory block is then deallocated, and the size and capacity of the vector are updated.
	 * The additional capacity created by the reallocation is filled with default-constructed elements of type T.
	 */
	void ReAlloc(const size_t newCapacity);

	/**
	 * @brief Reallocates memory for the vector with the specified new capacity and initializes
	 * the additional capacity with the specified default value.
	 * @param newCapacity The new capacity for the vector.
	 * @param defaultValue The default value used to initialize the additional capacity.
	 *
	 * If the new capacity is less than or equal to the current capacity, no reallocation is performed.
	 * Instead, the size of the vector is adjusted to match the new capacity.
	 * If the new capacity is greater than the current capacity, a new block of memory is allocated
	 * and the elements from the old block are moved to the new block.
	 * The old memory block is then deallocated, and the size and capacity of the vector are updated.
	 * The additional capacity created by the reallocation is filled with elements initialized with the specified default value.
	 */
	void ReAlloc(const size_t newCapacity, const T& defaultValue);
};


#include "../include/Vector.hpp"


template<class T>
inline Vector<T>::Vector() : m_Data(nullptr), m_Size(0), m_Capacity(0) {}

template<class T>
inline Vector<T>::Vector(size_t size, const T& defaultValue) : m_Size(size), m_Capacity(size)
{
	// check size validation
	if (size < 0)
	{
		throw std::invalid_argument("Invalid size: size must be <= 0");
	}

	// allocate new block of memory of m_capaicty
	this->m_Data = new T[m_Capacity];

	// set default value 
	std::fill(m_Data, m_Data + m_Size, defaultValue);
}

template<class T>
inline Vector<T>::Vector(std::initializer_list<T> values) : m_Size(values.size()), m_Capacity(values.size())
{
	// temprorly allcoate m_Data
	this->m_Data = new T[m_Capacity];

	// copy data from initializer list to out block of memory
	std::copy(values.begin(), values.end(), this->m_Data);
}

/* Shallow Copy */
//template<class T>
//Vector<T>::Vector(const Vector& otherVector) noexcept : m_Size(otherVector.m_Size), m_Capacity(otherVector.m_Capacity), m_Data(otherVector.m_Data)
//{
//}

/* Deep Copy */
template<class T>
inline Vector<T>::Vector(const Vector<T>& otherVector) : m_Size(otherVector.m_Size), m_Capacity(otherVector.m_Capacity)
{
	// performs deep copy
	this->m_Data = new T[m_Capacity];

	// take copy from data inside othervector to new allocated block (both will have independant memeory)
	std::copy(otherVector.m_Data, (otherVector.m_Data + otherVector.m_Size), this->m_Data);
}


template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& otherVector) noexcept
{
	// if this != otherVector, reallocate new block of memeory and copy data from other vector to this vector (perfrom deep copy)
	if (this != &otherVector)
	{
		// perfrom (deep copy)

		// delete current block of memeory (free it)
		delete[] this->m_Data;

		// re allocate new block with other capacity
		this->m_Size = otherVector.m_Size;
		this->m_Capacity = otherVector.m_Capacity;
		this->m_Data = new T[m_Capacity];

		// copy data from other to this
		std::copy(otherVector.m_Data, otherVector.m_Data + otherVector.m_Size, this->m_Data);
	}

	return *this;
}


template<class T>
inline Vector<T>::Vector(Vector<T>&& otherVector) noexcept : m_Size(0), m_Capacity(0), m_Data(nullptr)
{
	// move data from otherVector to this Vector	
	// 1. empty this vector 	
	// 2. pefrom shallow copy
	this->m_Size = otherVector.m_Size;
	this->m_Capacity = otherVector.m_Capacity;
	this->m_Data = otherVector.m_Data;

	// 2. set other vector to it's defualt state (empty state)
	otherVector.m_Size = 0;
	otherVector.m_Capacity = 0;
	otherVector.m_Data = nullptr;
}


template<class T>
inline Vector<T>&& Vector<T>::operator=(const Vector<T>&& otherVector)
{
	// if both notSharing same memeory
	if (this != &otherVector)
	{
		// move data from otherVector to this Vector
		// 1. empty this vector
		this->m_Size = 0;
		this->m_Capacity = 0;
		this->m_Data = nullptr;

		// 2. perfom shallow copy (if you won't set otherVecto to default state (empty) both share same memeory (such as alias)
		otherVector.m_Size = 0;
		otherVector.m_Capacity = 0;
		otherVector.m_Data = nullptr;
	}

	return *this;
}


template<class T>
inline Vector<T>::~Vector() noexcept
{
	// delete data raw pointer to prevent memory leak
	delete[] this->m_Data;
}

template<class T>
inline size_t Vector<T>::size() const
{
	return this->m_Size;
}

template<class T>
inline size_t Vector<T>::capacity() const
{
	return this->m_Capacity;
}


template<class T>
inline size_t Vector<T>::Max_Size() const
{
	// returns the max size this vector can reach (theoratically), in otherwords max of size_t
	return std::numeric_limits<size_t>::max();
}

template<class T>
inline bool Vector<T>::Empty() const
{
	return m_Size == 0;
}

template<class T>
inline bool Vector<T>::Full() const
{
	return m_Size == m_Capacity;
}

template<class T>
inline void Vector<T>::Reserve(size_t newCapacity)
{
	// Reserve memory for a specified capacity
	
	/*
	* 
	* If the specified capacity is greater than the current capacity of the vector:
	* Allocate a new memory block with the specified capacity.
	* If there are elements in the vector:
	* Copy the elements from the existing memory block to the new block.
	* Deallocate the old memory block.
	* Update the vector's capacity to the specified capacity.
	* 
	*/

	// if newCapacity <= current capacity, do nothing
	if (newCapacity <= m_Capacity) { return; }

	// reallocate new block of memory with given capacity
	ReAlloc(newCapacity);
}

template<class T>
inline void Vector<T>::Shrink_To_Fit()
{
	/*
	* Create a new memory block with a size equal to the current size of the vector.
	* Copy the elements from the existing memory block to the new block.
	* Deallocate the old memory block.
	* Set the vector's capacity to match its size.
	*/

	T* newBlock = new T[m_Size];
	std::copy(m_Data, (m_Data + m_Size), newBlock);
	delete[] m_Data;
	m_Data = newBlock;
	m_Capacity = m_Size;
}

template<class T>
inline const T& Vector<T>::Push_Back(const T& element)
{
	// if current block of memory is full reallcote new block with new capacity = 1.5old one
	if (this->Full())
	{
		ReAlloc(m_Capacity + m_Capacity / 2);
	}

	// add new element to the end of the vector
	m_Data[m_Size++] = element;
	return m_Data[m_Size - 1];

}

template<class T>
inline void Vector<T>::Push_Back(T&& element)
{
	if(Full())
	{
		// reallocate the memeory 
		ReAlloc(m_Capacity + m_Capacity / 2);
	}

	new (&m_Data[m_Size]) T(std::move(element));
}

template<class T>
inline T Vector<T>::Pop_Back()
{
	if (!Empty())
	{
		// reduce size by one
		// take copy from the last element
		// destruct the last element 
		// returh its copy
		--m_Size;
		T poppedElement = std::move(m_Data[m_Size]); // note m_Size has been decreased by one (now it's same as index)
		m_Data[m_Size].~T();
		return poppedElement;
		
	}
	else
	{
		// return default value of T();
		return T();
	}
}

template<class T>
inline void Vector<T>::Resize(size_t newSize)
{
	ReAlloc(newSize);
	
}

template<class T>
inline void Vector<T>::Resize(size_t newSize, const T& defaultValue)
{
	ReAlloc(newSize, defaultValue);
}

template<class T>
inline void Vector<T>::Swap(Vector<T>& v)
{
	std::swap(m_Size, v.m_Size);
	std::swap(m_Capacity, v.m_Capacity);
	std::swap(m_Data, v.m_Data);
}

template<class T>
inline void Vector<T>::Clear()
{
	// if vector is already empty do nothing
	if (Empty()){ return; }

	// clear 
	for (size_t i = 0; i < m_Size; ++i)
	{
		// destruct all element in m_Data
		m_Data[i].~T();		
	}

	// set size = 0, capacity still the same, as we have same block of memory
	m_Size = 0;
}

template<class T>
inline T Vector<T>::Erase(const size_t& index)
{
	// flag
	bool erased = true;

	// check if index in range
	if (index >= m_Size)
	{
		return T();
	}
	
	// store element to be erased
	T erasedElement = m_Data[index];

	// erase by shifting all element left o(n)
	for(size_t i = index; i < m_Size - 1; ++i)
	{
		m_Data[i] = m_Data[i + 1];
	}

	// reduce size by one
	--m_Size;

	return erasedElement;
}
template<class T>
inline void Vector<T>::Erase(typename Vector<T>::iterator it)
{
	size_t index = it - begin();
	if (index >= m_Size)
	{
		// Invalid index
		return;
	}

	if (index == m_Size - 1)
	{
		// Special case when removing the last element
		--m_Size;
		return;
	}

	// Remove element at index by shifting elements left
	for (size_t i = index; i < m_Size - 1; ++i)
	{
		m_Data[i] = m_Data[i + 1];
	}

	// Decrement size by one
	--m_Size;
}

template<class T>
void Vector<T>::Erase(typename Vector<T>::iterator first, typename Vector<T>::iterator last)
{
	size_t rangeSize = std::distance(first, last); // Calculate the size of the range

	if (rangeSize <= 0)
	{
		// No elements to erase
		return;
	}

	size_t startIndex = std::distance(begin(), first); // Calculate the index of the first element in the range

	if (startIndex >= m_Size)
	{
		// Invalid range
		return;
	}

	size_t endIndex = startIndex + rangeSize; // Calculate the index of the element after the last element in the range

	if (endIndex > m_Size)
	{
		// Adjust the endIndex if it goes beyond the vector size
		endIndex = m_Size;
	}

	size_t numElementsAfterRange = m_Size - endIndex; // Calculate the number of elements after the range

	// Move the elements after the range to fill the gap created by the erased range
	for (size_t i = 0; i < numElementsAfterRange; ++i)
	{
		m_Data[startIndex + i] = m_Data[endIndex + i];
	}

	m_Size -= rangeSize; // Update the size of the vector
}

template<class T>
const T& Vector<T>::Insert(const size_t& index, const T& element)
{
	if (index >= m_Size || index < 0)
	{
		throw std::out_of_range("Invalid index: index is out of range!");
	}

	if (m_Size == m_Capacity)
	{
		// If the vector is full, reallocate with increased capacity
		ReAlloc(m_Capacity + m_Capacity / 2);
	}

	// Shift elements to the right to make space for the new element
	for (size_t i = m_Size; i > index; --i)
	{
		m_Data[i] = m_Data[i - 1];
	}

	// Insert the new element at the specified index
	m_Data[index] = element;
	++m_Size;

	return m_Data[index];
}

template<class T>
void Vector<T>::Insert(iterator pos, const T& element)
{
	size_t index = std::distance(begin(), pos); // Calculate the index of the iterator

	this->Insert(index, element);
}
template<class T>
void Vector<T>::Insert(iterator pos, std::initializer_list<T> elements)
{
	size_t insertIndex = pos - begin();

	if (insertIndex > m_Size)
	{
		throw std::out_of_range("Invalid position: position is out of range!");
	}

	size_t elementsCount = elements.size();
	size_t newSize = m_Size + elementsCount;

	if (newSize > m_Capacity)
	{
		// If the vector capacity is not enough, reallocate with increased capacity
		size_t newCapacity = std::max(m_Capacity + m_Capacity / 2, newSize);
		ReAlloc(newCapacity);
	}

	// Shift elements to the right to make space for the new elements
	for (size_t i = m_Size; i > insertIndex; --i)
	{
		m_Data[i + elementsCount - 1] = std::move(m_Data[i - 1]);
	}

	// Copy the elements from the initializer list to the vector
	size_t currentIndex = insertIndex;
	for (const T& element : elements)
	{
		m_Data[currentIndex++] = element;
	}

	m_Size = newSize;
}






////////////////////////////////////////////// Operators Overloadings //////////////////////
template<class T>
inline const T& Vector<T>::operator[](size_t index) const
{
	if (index >= m_Size || index < 0)
	{
		throw std::invalid_argument("Invalid index: index is out or range");
	}

	return m_Data[index];
}

template<class T>
inline T& Vector<T>::operator[](size_t index)
{
	if (index >= m_Size || index < 0)
	{
		throw std::invalid_argument("Invalid index: index is out of range");
	}
	return m_Data[index];
}
template<class T>
bool Vector<T>::operator<(const Vector<T>& otherVector) const
{
	// compare in terms of size
	if (this->m_Size != otherVector.m_Size) {
		return this->m_Size < otherVector.m_Size;
	}

	// both have same size, compare element by element till a pair satisfies the condition
	for (size_t i = 0; i < this->m_Size; ++i) {
		if (std::less<T>()(this->m_Data[i], otherVector.m_Data[i])) {
			return true;
		}
		else if (std::less<T>()(otherVector.m_Data[i], this->m_Data[i])) {
			return false;
		}
	}

	return false; // Both vectors are equal
}

template<class T>
bool Vector<T>::operator>(const Vector<T>& otherVector) const
{
	// compare in temrs of size
	if (this->m_Size != otherVector.m_Size) {
		return this->m_Size > otherVector.m_Size;
	}

	// if both are equal compare elements
	for (size_t i = 0; i < this->m_Size; ++i) {
		if (std::less<T>()(otherVector.m_Data[i], this->m_Data[i])) {
			return true;
		}
		else if (std::less<T>()(this->m_Data[i], otherVector.m_Data[i])) {
			return false;
		}
	}

	return false; // Both vectors are equal
}

template<class T>
bool Vector<T>::operator==(const Vector<T>& otherVector) const
{
	// compare in terms of size
	if (this->m_Size != otherVector.m_Size) {
		return false;
	}

	// both have the same size compar each element with its correspondent in otherVector
	for (size_t i = 0; i < this->m_Size; ++i) {
		if (this->m_Data[i] != otherVector.m_Data[i]) {
			return false;
		}
	}

	return true; // Vectors are equal
}

template<class T>
bool Vector<T>::operator<=(const Vector<T>& otherVector) const
{
	return (*this < otherVector) || (*this == otherVector);
}

template<class T>
bool Vector<T>::operator>=(const Vector<T>& otherVector) const
{
	return (*this > otherVector) || (*this == otherVector);
}

template<class T>
bool Vector<T>::operator!=(const Vector<T>& otherVector) const
{
	return !(*this == otherVector);
}


template<class T>
Vector<T> Vector<T>::operator+(const Vector<T>& otherVector) const
{
	size_t newSize = this->m_Size + otherVector.m_Size;
	Vector<T> result(newSize);

	// o(n)
	for (size_t i = 0; i < this->m_Size; ++i)
	{
		result[i] = this->m_Data[i];
	}

	// o(k)
	for (size_t i = 0; i < otherVector.m_Size; ++i)
	{
		result[this->m_Size + i] = otherVector[i];
	}
	//o(n + k)
	return result;
}

template<class T>
inline Vector<T> Vector<T>::operator+(const T& scalar) const
{
	if (size == 0) { return *this; }
	Vector<T> result(this->m_Size);
	for(size_t i = 0; i < this->m_Size;++i)
	{
		result[i] = this->m_Data[i] + scalar;
	}

	return result;
}

template<class T>
Vector<T> Vector<T>::operator-(const Vector<T>& otherVector) const
{
	size_t newSize = std::max(this->m_Size, otherVector.m_Size);
	Vector<T> result(newSize);

	for (size_t i = 0; i < newSize; ++i)
	{
		T value = (i < this->m_Size) ? this->m_Data[i] : T();
		T otherValue = (i < otherVector.m_Size) ? otherVector[i] : T{};
		result[i] = value - otherValue;
	}

	return result;
}

template<class T>
Vector<T> Vector<T>::operator-(const T& scalar) const
{
	Vector<T> result(this->m_Size);

	for (size_t i = 0; i < m_Size; ++i)
	{
		result[i] = this->m_Data[i] - scalar;
	}

	return result;
}


template<class T>
Vector<T> Vector<T>::operator*(const Vector<T>& otherVector) const
{
	/*
	* Algorithm
	* 1. both must have same size if not throw invalid argumen
	* 2. create a new result object 
	* 3. multiply each element with its correspondent;
	* 4. return result
	*/
	if (this->m_Size != otherVector.m_Size)
	{
		throw std::invalid_argument("Invalid argument: Vector sizes are not equal");
	}
 
	Vector<T> result(this->m_Size);

	for (size_t i = 0; i < this->m_Size; ++i)		// o(n);
	{
		result[i] = otherVector[i] * this->m_Data[i];
	}

	return result;
}

template<class T>
inline Vector<T> Vector<T>::operator*(const T& scalar) const
{
	/*
	* In this version, it takes a scaler and multiply each element in the vector with it
	*/

	Vector<T> result(this->m_Size);
	for(size_t i = 0; i < this->m_Size; ++i)
	{
		result[i] = this->m_Data[i] * scalar;
	}

	return result;

}



template<class T>
Vector<T> Vector<T>::operator/(const Vector<T>& otherVector) const
{
	/*
	* Algorithm ( elment wise divsion of corresponend elements)
	* 1. if (both vectores sizes not equal, throw invalid_ argument excpetion
	* 2. create a result vector and result[i] = this->m_Data[i] / other[i];
	* 3. return the restul
	*/

	if (this->m_Size != otherVector.m_Size)
	{
		throw std::invalid_argument("Invalid argument: Vector sizes are not equal");
	}

	Vector<T> result(this->m_Size);

	for(size_t i = 0; i < this->m_Size; ++i)
	{
		result[i] = this->m_Data[i] / otherVector[i];
	}

	return result;
}

template<class T>
inline Vector<T> Vector<T>::operator/(const T& scalar)const
{
	/*
	* Algorithm (scalar version)
	* 1. divide each element of this over scalar
	* 2. return scalar
	*/

	Vector<T> result(this->m_Size);
	for(size_t i = 0; i < m_Size; ++i)
	{
		result[i] = this->m_Data[i] / scalar;
	}

	// o(n)
	return result;
}



/////////////////////////////////////////////// Iterators ////////////////////////////////////
template<class T>
inline typename Vector<T>::iterator Vector<T>::begin()
{
	return iterator(this->m_Data);
}

template<class T>
inline typename Vector<T>::iterator Vector<T>::end()
{
	return iterator(this->m_Data + m_Size);
}

////////////////////////////////////////////// Helper Methods //////////////////////////////
template<class T>
void Vector<T>::ReAlloc(const size_t newCapacity)
{
	// newCapacity <= oldCapacity, change no need to reallocate new block instead change the value of both size and capacity
	if (newCapacity <= this->m_Capacity) 
	{
		this->m_Size = newCapacity;
		this->m_Capacity = m_Size;
		return;
	}
	
	// register new block of memeory of type t
	// move data from old block to new block
	// delete old block
	// init the extra capacity with zeros
	// set this->m_Data = newBlock

	T* newBlock = new T[newCapacity];
	std::copy(this->m_Data, this->m_Data + this->m_Size, newBlock);
	delete[] this->m_Data;
	this->m_Data = newBlock;
	std::fill((m_Data + m_Size), (m_Data + newCapacity), 0);
	this->m_Capacity = newCapacity;
}

template<class T>
void Vector<T>::ReAlloc(const size_t newCapacity, const T& defaultValue)
{
	// newCapacity <= oldCapacity, change no need to reallocate new block instead change the value of both size and capacity
	if (newCapacity <= this->m_Capacity)
	{
		this->m_Size = newCapacity;
		this->m_Capacity = m_Size;
		return;
	}

	// register new block of memeory of type t
	// move data from old block to new block
	// delete old block
	// init the extra capacity with zeros
	// set this->m_Data = newBlock

	T* newBlock = new T[newCapacity];
	std::copy(this->m_Data, this->m_Data + this->m_Size, newBlock);
	delete[] this->m_Data;
	this->m_Data = newBlock;
	std::fill((m_Data + m_Size), (m_Data + newCapacity), defaultValue);
	this->m_Capacity = newCapacity;
}

template<class T>
inline const T& Vector<T>::At(size_t index) const
{
	return (*this)[index];
}

template<class T>
inline T& Vector<T>::At(size_t index)
{
	return (*this)[index];
}

template<class T>
inline T& Vector<T>::Back()
{
	// if vector is empty throw out of range excpetion
	if (m_Size == 0)
	{
		throw std::out_of_range("Invalid range: vector is empty!");
	}

	return m_Data[m_Size - 1];
	
}

template<class T>
inline const T& Vector<T>::Back() const
{
	// if vector is empty throw out of range excpetion
	if (m_Size == 0)
	{
		throw std::out_of_range("Invalid range: vector is empty!");
	}

	return m_Data[m_Size - 1];
}

template<class T>
inline T& Vector<T>::Front()
{
	// if vector is empty throw out of range excpetion
	if (m_Size == 0)
	{
		throw std::out_of_range("Invalid range: vector is empty!");
	}

	return m_Data[0];
}

template <class T>
inline const T& Vector<T>::Front() const
{
	if (m_Size == 0)
	{
		throw std::out_of_range("Invalid range: vector is empty!");
	}

	return m_Data[0];
}

template<class T>
inline T* Vector<T>::Data()
{
	// works as a getter method of m_Data;
	return this->m_Data;
}


template <class T>
inline const T* Vector<T>::Data() const
{
	return this->m_Data;
}
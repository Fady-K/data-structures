#include <iostream>
#include <iterator>

template <class T>
class Iterator
{
	/* Insatnce Attributes */
private:
	T* m_Current;					// pointer to the current element

	/* constructor and Instance Methods */
public:
	using iterator_category = std::forward_iterator_tag;			// iterator category
	using value_type = T;											// type of elements being iterated		
	using difference_type = std::ptrdiff_t;							// for measuring instance between iterators
	using pointer = T*;												// pointer to the iterated elements
	using reference = T&;											// reference to data being iterated

	// constructors
	explicit Iterator() noexcept;											// default constructor
	Iterator(T* ptr);												// parametrized constructor
	Iterator(const Iterator& it) noexcept;							// default copy constructor
	Iterator(Iterator&& it)	noexcept;								// move constructor
	Iterator<T>& operator=(const Iterator<T>& it);						// copy assignment operator
	Iterator<T>& operator=(Iterator<T>&& it);								// move assignment operator
	~Iterator() noexcept;											// destructor

	
	// setters and getters (encapsulation)
	void setCurrentPointer(T* ptr);
	T* getCurrentPointer() const;


	// operators overloadings
	T& operator*() const;											// Dereference operator
	T* operator->() const;											// Arrow operator

	Iterator<T>& operator++();										// pre increment operator	(++it)
	Iterator<T> operator++(const int) ;								// post incrmenet operator	(it++)

	Iterator<T>& operator--();										// pre decrement operator (--it)
	Iterator<T>& operator--(int);									// post decrement operator (it--)

	Iterator<T>& operator+(difference_type n);
	Iterator<T> operator+(const Iterator<T>& it);
	Iterator<T>& operator-(difference_type n);
	size_t operator-(const Iterator<T>& it);

	Iterator<T>& operator+=(difference_type n);
	Iterator<T>& operator-=(difference_type n);


	bool operator==(const Iterator<T>& it) const;					// equality operator
	bool operator!=(const Iterator<T>& it) const;					// inequailty operator

	//// friend operators
	//friend std::ostream& operator<<(std::ostream& output, const Iterator<T>& it);
	//friend std::istream& operator>>(std::istream& input, Iterator<T>& it);
};
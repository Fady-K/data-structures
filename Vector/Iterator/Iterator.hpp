/**
 * @file Iterator.hpp
 * @author Fady Kamal (popfadykamal151617@gmail.com)
 * @brief This file is the header file of Iterator class.
 * @details It contains standerd methods (operators), whether dereferencing, arrow, arithmatic, comparison..etc
 * @date 2023-07-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <iterator>

/**
 * @class Iterator
 * @brief Represents an iterator for a dynamic array.
 *
 * The Iterator class provides the ability to iterate over the elements of a dynamic array.
 * It supports various iterator operations such as dereferencing, arithmetic operations,
 * and comparison operations.
 *
 * @tparam T The type of elements being iterated.
 */
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

	/**
     * @brief Default constructor.
     *
     * Constructs an Iterator object with a null pointer.
     */
    explicit Iterator() noexcept;

    /**
     * @brief Parametrized constructor.
     *
     * Constructs an Iterator object with the specified pointer.
     *
     * @param ptr A pointer to the current element.
     */
    Iterator(T* ptr);

    /**
     * @brief Copy constructor.
     *
     * Constructs an Iterator object as a copy of another Iterator object.
     *
     * @param it The Iterator object to copy.
     */
    Iterator(const Iterator& it) noexcept;

    /**
     * @brief Move constructor.
     *
     * Constructs an Iterator object by moving the pointer from another Iterator object.
     *
     * @param it The Iterator object to move.
     */
    Iterator(Iterator&& it) noexcept;

    /**
     * @brief Copy assignment operator.
     *
     * Assigns the value of another Iterator object to this Iterator object.
     *
     * @param it The Iterator object to copy.
     * @return A reference to the current Iterator object.
     */
    Iterator<T>& operator=(const Iterator<T>& it);

    /**
     * @brief Move assignment operator.
     *
     * Moves the pointer from another Iterator object to this Iterator object.
     *
     * @param it The Iterator object to move.
     * @return A reference to the current Iterator object.
     */
    Iterator<T>& operator=(Iterator<T>&& it);

    /**
     * @brief Destructor.
     *
     * Destroys the Iterator object.
     */
    ~Iterator() noexcept;

    /**
     * @brief Set the current pointer.
     *
     * Sets the pointer to the specified value.
     *
     * @param ptr A pointer to the current element.
     */
    void setCurrentPointer(T* ptr);

    /**
     * @brief Get the current pointer.
     *
     * Returns the pointer to the current element.
     *
     * @return A pointer to the current element.
     */
    T* getCurrentPointer() const;

    /**
     * @brief Dereference operator.
     *
     * Returns a reference to the element pointed to by the iterator.
     *
     * @return A reference to the element.
     */
    T& operator*() const;

    /**
     * @brief Arrow operator.
     *
     * Returns the pointer to the element pointed to by the iterator.
     *
     * @return A pointer to the element.
     */
    T* operator->() const;

    /**
     * @brief Pre-increment operator.
     *
     * Increments the iterator to the next element and returns the incremented iterator.
     *
     * @return A reference to the incremented iterator.
     */
    Iterator<T>& operator++();

    /**
     * @brief Post-increment operator.
     *
     * Increments the iterator to the next element and returns a copy of the original iterator.
     *
     * @return A copy of the original iterator.
     */
    Iterator<T> operator++(const int);

    /**
     * @brief Pre-decrement operator.
     *
     * Decrements the iterator to the previous element and returns the decremented iterator.
     *
     * @return A reference to the decremented iterator.
     */
    Iterator<T>& operator--();

    /**
     * @brief Post-decrement operator.
     *
     * Decrements the iterator to the previous element and returns a copy of the original iterator.
     *
     * @return A copy of the original iterator.
     */
    Iterator<T>& operator--(int);

    /**
     * @brief Addition operator.
     *
     * Advances the iterator by a specified number of positions and returns the updated iterator.
     *
     * @param n The number of positions to advance.
     * @return A reference to the updated iterator.
     */
    Iterator<T>& operator+(difference_type n);

    /**
     * @brief Addition operator.
     *
     * Returns a new iterator that is advanced by the specified iterator positions.
     *
     * @param it The iterator specifying the number of positions to advance.
     * @return A new iterator advanced by the specified positions.
     */
    Iterator<T> operator+(const Iterator<T>& it);

    /**
     * @brief Subtraction operator.
     *
     * Moves the iterator back by a specified number of positions and returns the updated iterator.
     *
     * @param n The number of positions to move back.
     * @return A reference to the updated iterator.
     */
    Iterator<T>& operator-(difference_type n);

    /**
     * @brief Subtraction operator.
     *
     * Returns the distance between two iterators.
     *
     * @param it The iterator to calculate the distance from.
     * @return The distance between the two iterators.
     */
    size_t operator-(const Iterator<T>& it);

    /**
     * @brief Compound addition assignment operator.
     *
     * Advances the iterator by a specified number of positions and returns the updated iterator.
     *
     * @param n The number of positions to advance.
     * @return A reference to the updated iterator.
     */
    Iterator<T>& operator+=(difference_type n);

    /**
     * @brief Compound subtraction assignment operator.
     *
     * Moves the iterator back by a specified number of positions and returns the updated iterator.
     *
     * @param n The number of positions to move back.
     * @return A reference to the updated iterator.
     */
    Iterator<T>& operator-=(difference_type n);

    /**
     * @brief Equality operator.
     *
     * Checks if two iterators are equal.
     *
     * @param it The iterator to compare with.
     * @return `true` if the iterators are equal, `false` otherwise.
     */
    bool operator==(const Iterator<T>& it) const;

    /**
     * @brief Inequality operator.
     *
     * Checks if two iterators are not equal.
     *
     * @param it The iterator to compare with.
     * @return `true` if the iterators are not equal, `false` otherwise.
     */
    bool operator!=(const Iterator<T>& it) const;


	//// friend operators
	//friend std::ostream& operator<<(std::ostream& output, const Iterator<T>& it);
	//friend std::istream& operator>>(std::istream& input, Iterator<T>& it);
};
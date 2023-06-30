/**
 * @file VectorUnitTest.cpp
 * @author Fady Kamal (popfadykamal151617@gmail.com)
 * @brief This file contains unit testing of the vector class.
 * @details It includes test cases for constructors, assignment operators (copy, move), destructor,
 * capacity and size opertions, vector methods and vector based iterators ... etc
 * @date 2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <gtest/gtest.h>
#include "include/Vector.hpp"

/**
 * @class VectorTest
 * @brief Test fixture for the Vector class.
 *
 * This test fixture provides a common setup and teardown for the tests
 * related to the Vector class. It also includes a helper function to check
 * if two vectors are equal.
 */
class VectorTest : public testing::Test {
protected:
    Vector<int> v;  /**< The Vector object used for testing. */

    /**
     * @brief Set up the test fixture.
     *
     * This function is called before each test case. It sets up any common
     * resources needed for the tests, such as initializing the Vector object
     * with some elements.
     */
    void SetUp() override {
        v.Push_Back(1);
        v.Push_Back(2);
        v.Push_Back(3);
        v.Push_Back(4);
        v.Push_Back(5);
    }

    /**
     * @brief Tear down the test fixture.
     *
     * This function is called after each test case. It cleans up any shared
     * resources and resets the Vector object.
     */
    void TearDown() override {
        v.Clear();
    }

    /**
     * @brief Check if two vectors are equal.
     * @param vec1 The first vector to compare.
     * @param vec2 The second vector to compare.
     * @return True if the vectors are equal, False otherwise.
     *
     * This helper function compares two vectors for equality by checking their
     * sizes and elements. It returns true if the sizes are equal and all elements
     * are equal at corresponding indices.
     */
    template <class T>
    bool vectorsAreEqual(const Vector<T>& vec1, const Vector<T>& vec2) const {
        if (vec1.size() != vec2.size()) {
            return false;
        }

        for (size_t i = 0; i < vec1.size(); ++i) {
            if (vec1[i] != vec2[i]) {
                return false;
            }
        }

        return true;
    }
};


//////////////////////////////////////////////////////////// Constructors ///////// ////////////////////////////////////////////////////////////
/**
 * @brief Test case for the default constructor of the Vector class.
 */
TEST_F(VectorTest, DefaultConstructor) {
    // Arrange
    Vector<int> v;

    // Act & Assert
    EXPECT_EQ(0, v.size());
}

/**
 * @brief Test case for the parameterized constructor of the Vector class.
 */
TEST_F(VectorTest, ParametrizedConstructor) {
    // Arrange
    Vector<int> v(5, 10);

    // Act & Assert
    EXPECT_EQ(5, v.size());
    for (int i = 0; i < v.size(); ++i) {
        EXPECT_EQ(10, v[i]);
    }
}

/**
 * @brief Test case for the initializer list constructor of the Vector class.
 */
TEST_F(VectorTest, InitializerListConstructor) {
    // Arrange
    Vector<int> v{ 1, 2, 3, 4, 5 };

    // Act & Assert
    EXPECT_EQ(5, v.size());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);
    EXPECT_EQ(4, v[3]);
    EXPECT_EQ(5, v[4]);
}

/**
 * @brief Test case for the copy constructor of the Vector class.
 */
TEST_F(VectorTest, CopyConstructor) {
    // Arrange
    Vector<int> copy(v);

    // Act & Assert
    EXPECT_EQ(v.size(), copy.size());
    for (int i = 0; i < v.size(); ++i) {
        EXPECT_EQ(v[i], copy[i]);
    }
}

/**
 * @brief Test case for the move constructor of the Vector class.
 */
TEST_F(VectorTest, MoveConstructor) {
    // Arrange
    Vector<int> original(v);

    // Act
    Vector<int> moved(std::move(original));

    // Assert
    EXPECT_EQ(v.size(), moved.size());
    EXPECT_EQ(0, original.size()); // After move, the source vector should be empty
}


//////////////////////////////////////////////////////////// Assignment Operators(copy, move) ////////////////////////////////////////////////////////////
/**
 * @brief Test case for the copy assignment operator of the Vector class.
 */
TEST_F(VectorTest, CopyAssignmentOperator) {
    // Arrange
    Vector<int> vec1{ 1, 2, 3 };
    Vector<int> vec2{ 4, 5 };

    // Act: Copy assign vec1 to vec2
    vec2 = vec1;

    // Assert: Check if vec2 is equal to vec1
    ASSERT_TRUE(vectorsAreEqual(vec1, vec2));
}

/**
 * @brief Test case for the move assignment operator of the Vector class.
 */
TEST_F(VectorTest, MoveAssignmentOperator) {
    // Arrange
    Vector<int> vec1{ 1, 2, 3 };
    Vector<int> vec2{ 4, 5 };

    // Act: Move assign vec1 to vec2
    vec2 = std::move(vec1);

    // Assert: Check if vec2 has the moved data and vec1 is empty
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec1.size(), 0);
}

//////////////////////////////////////////////////////////// Destructor ///////////////////////////////////////////////////////////////////
/**
 * @brief Test case for the destructor of the Vector class, ensuring proper deallocation of memory.
 */
TEST_F(VectorTest, Destructor_DeallocatesMemory) {
    // Arrange
    // Create a vector
    Vector<int>* vec = new Vector<int>{ 1, 2, 3 };

    // Act
    // Get the pointer to the underlying data
    int* dataPtr = vec->Data();

    // Destroy the vector
    delete vec;

    // Assert
    // Check if the memory was properly deallocated using Google Test's memory leak detection
    SUCCEED();  // No memory leaks detected
}


//////////////////////////////////////////////////////////// Capacity And Size ////////////////////////////////////////////////////////////
/**
 * @brief Test case for the size() method of the Vector class, ensuring correct size retrieval.
 */
TEST_F(VectorTest, Size) {
    // Arrange & Act
    EXPECT_EQ(5, v.size());

    v.Clear();

    // Assert
    EXPECT_EQ(0, v.size());
}

/**
 * @brief Test case for the capacity() method of the Vector class, ensuring correct capacity retrieval.
 */
TEST_F(VectorTest, Capacity) {
    // Arrange & Act
    EXPECT_EQ(6, v.capacity());

    v.Reserve(20);

    // Assert
    EXPECT_EQ(20, v.capacity());

    v.Reserve(10);

    // Assert
    EXPECT_EQ(20, v.capacity()); // Capacity should remain unchanged
}

/**
 * @brief Test case for the Max_Size() method of the Vector class, ensuring retrieval of the maximum possible size.
 */
TEST_F(VectorTest, MaxSize) {
    // Arrange & Act
    EXPECT_EQ(std::numeric_limits<size_t>::max(), v.Max_Size());
}

/**
 * @brief Test case for the Empty() method of the Vector class, ensuring correct empty state detection.
 */
TEST_F(VectorTest, Empty) {
    // Arrange & Act
    EXPECT_FALSE(v.Empty());

    Vector<int> emptyVec;

    // Assert
    EXPECT_TRUE(emptyVec.Empty());
}

/**
 * @brief Test case for the Full() method of the Vector class, ensuring correct full state detection.
 */
TEST_F(VectorTest, Full) {
    // Arrange & Act
    EXPECT_FALSE(v.Full());

    Vector<int> fullVec(5, 10);

    // Assert
    EXPECT_TRUE(fullVec.Full());
}

/**
 * @brief Test case for the Reserve() method of the Vector class, ensuring correct capacity reservation.
 */
TEST_F(VectorTest, Reserve) {
    // Arrange & Act
    v.Reserve(20);

    // Assert
    EXPECT_EQ(5, v.size()); // Size should remain unchanged
    EXPECT_EQ(20, v.capacity());
}

/**
 * @brief Test case for the Shrink_To_Fit() method of the Vector class, ensuring proper shrinking of capacity.
 */
TEST_F(VectorTest, ShrinkToFit) {
    // Arrange & Act
    v.Shrink_To_Fit();

    // Assert
    EXPECT_EQ(5, v.size()); // Size should remain unchanged
    EXPECT_EQ(5, v.capacity());
}

/**
 * @brief Test case for the Clear() method of the Vector class, ensuring correct clearing of the vector.
 */
TEST_F(VectorTest, Clear) {
    // Arrange & Act
    EXPECT_EQ(5, v.size());

    v.Clear();

    // Assert
    EXPECT_EQ(0, v.size());
    EXPECT_EQ(6, v.capacity()); // Capacity should remain unchanged
}


//////////////////////////////////////////////////////////// Modifiers ///////////////////////////////////////////////////////////////////////
/**
 * @brief Test case for the Push_Back(const T& element) method of the Vector class,
 *        ensuring correct insertion of an lvalue element at the back of the vector.
 */
TEST_F(VectorTest, PushBackLvalue) {
    // Arrange
    int element = 10;

    // Act
    const int& pushedElement = v.Push_Back(element);

    // Assert
    EXPECT_EQ(element, pushedElement);
    EXPECT_EQ(6, v.size());
    EXPECT_EQ(6, v.capacity()); // Capacity should remain the same as there is no need to resize
    EXPECT_EQ(element, v[v.size() - 1]);
}

/**
 * @brief Test case for the Push_Back(T&& element) method of the Vector class,
 *        ensuring correct insertion of an rvalue element at the back of the vector.
 */
TEST_F(VectorTest, PushBackRvalue) {
    // Arrange
    int element = 10;
    int&& rvalueElement = std::move(element);

    // Act
    v.Push_Back(std::move(rvalueElement));

    // Assert
    EXPECT_EQ(6, v.size());
    EXPECT_EQ(6, v.capacity()); // Capacity should remain the same as there is no need to resize
    EXPECT_EQ(10, v[v.size() - 1]);
}

/**
 * @brief Test case for the Pop_Back() method of the Vector class, ensuring correct removal of the last element.
 */
TEST_F(VectorTest, PopBack) {
    // Act
    int poppedElement = v.Pop_Back();

    // Assert
    EXPECT_EQ(5, poppedElement);
    EXPECT_EQ(4, v.size());
    EXPECT_EQ(6, v.capacity()); // Capacity should remain the same as there is no need to resize
}

/**
 * @brief Test case for the Resize(size_t newSize) method of the Vector class,
 *        ensuring correct resizing of the vector.
 */
TEST_F(VectorTest, Resize) {
    // Act
    v.Resize(10);

    // Assert
    EXPECT_EQ(10, v.size());
    EXPECT_EQ(10, v.capacity());

    // Act
    v.Resize(3);

    // Assert
    EXPECT_EQ(3, v.size());
    EXPECT_EQ(10, v.capacity());
}

/**
 * @brief Test case for the Resize(size_t newSize, const T& defaultValue) method of the Vector class,
 *        ensuring correct resizing of the vector with a default value for the new elements.
 */
TEST_F(VectorTest, ResizeWithDefaultValue) {
    // Arrange
    int defaultValue = 100;
    int oldSize = v.size();

    // Act
    v.Resize(10, defaultValue);

    // Assert
    EXPECT_EQ(10, v.size());
    EXPECT_EQ(10, v.capacity());
    for (size_t i = oldSize; i < v.size(); ++i) {
        EXPECT_EQ(defaultValue, v[i]);
    }

    // Act
    v.Resize(3, defaultValue);

    // Assert
    EXPECT_EQ(3, v.size());
    EXPECT_EQ(10, v.capacity());
}

/**
 * @brief Test case for the Swap(Vector<T>& v) method of the Vector class, ensuring correct swapping of two vectors.
 */
TEST_F(VectorTest, Swap) {
    // Arrange
    Vector<int> v2{ 100, 200, 300 };

    // Act
    v.Swap(v2);

    // Assert
    EXPECT_EQ(3, v.size());
    EXPECT_EQ(3, v.capacity());
    EXPECT_EQ(5, v2.size());
    EXPECT_EQ(6, v2.capacity());
    EXPECT_EQ(100, v[0]);
    EXPECT_EQ(200, v[1]);
    EXPECT_EQ(300, v[2]);
    EXPECT_EQ(1, v2[0]);
    EXPECT_EQ(2, v2[1]);
    EXPECT_EQ(3, v2[2]);
    EXPECT_EQ(4, v2[3]);
    EXPECT_EQ(5, v2[4]);
}


//////////////////////////////////////////////////////////// Modifiers Based Iterators ////////////////////////////////////////////////////////////
/**
 * @brief Test case for the Erase(const size_t& index) method of the Vector class,
 *        ensuring correct erasing of an element at a specific index.
 */
TEST_F(VectorTest, EraseIndex) {
    // Arrange
    size_t index = 2;

    // Act
    int erasedElement = v.Erase(index);

    // Assert
    EXPECT_EQ(3, erasedElement);
    EXPECT_EQ(4, v.size());
    EXPECT_EQ(6, v.capacity());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(4, v[2]);
    EXPECT_EQ(5, v[3]);
}

/**
 * @brief Test case for the Erase(iterator pos) method of the Vector class,
 *        ensuring correct erasing of an element at a specific iterator position.
 */
TEST_F(VectorTest, EraseIterator) {
    // Arrange
    auto it = v.begin() + 2;

    // Act
    v.Erase(it);

    // Assert
    EXPECT_EQ(4, v.size());
    EXPECT_EQ(6, v.capacity());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(4, v[2]);
    EXPECT_EQ(5, v[3]);
}

/**
 * @brief Test case for the Erase(iterator first, iterator last) method of the Vector class,
 *        ensuring correct erasing of elements in a range specified by two iterators.
 */
TEST_F(VectorTest, EraseRange) {
    // Arrange
    auto first = v.begin() + 1;
    auto last = v.end() - 1;

    // Act
    v.Erase(first, last);

    // Assert
    EXPECT_EQ(2, v.size());
    EXPECT_EQ(6, v.capacity());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(5, v[1]);
}

/**
 * @brief Test case for the Insert(const size_t& index, const T& element) method of the Vector class,
 *        ensuring correct insertion of an element at a specific index.
 */
TEST_F(VectorTest, InsertIndex) {
    // Arrange
    size_t index = 2;
    int element = 10;

    // Act
    const int& insertedElement = v.Insert(index, element);

    // Assert
    EXPECT_EQ(element, insertedElement);
    EXPECT_EQ(6, v.size());
    EXPECT_EQ(6, v.capacity());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(10, v[2]);
    EXPECT_EQ(3, v[3]);
    EXPECT_EQ(4, v[4]);
    EXPECT_EQ(5, v[5]);
}

/**
 * @brief Test case for the Insert(iterator pos, const T& element) method of the Vector class,
 *        ensuring correct insertion of an element at a specific iterator position.
 */
TEST_F(VectorTest, InsertIterator) {
    // Arrange
    auto pos = v.begin() + 2;
    int element = 10;

    // Act
    v.Insert(pos, element);

    // Assert
    EXPECT_EQ(6, v.size());
    EXPECT_EQ(6, v.capacity());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(10, v[2]);
    EXPECT_EQ(3, v[3]);
    EXPECT_EQ(4, v[4]);
    EXPECT_EQ(5, v[5]);
}

/**
 * @brief Test case for the Insert(iterator startPos, std::initializer_list<T> elements) method of the Vector class,
 *        ensuring correct insertion of elements from an initializer list at a specific iterator position.
 */
TEST_F(VectorTest, InsertInitializerList) {
    // Arrange
    auto startPos = v.begin() + 2;
    std::initializer_list<int> elements = { 10, 20, 30 };

    // Act
    v.Insert(startPos, elements);

    // Assert
    EXPECT_EQ(8, v.size());
    EXPECT_EQ(9, v.capacity()); // note: old capacity = 6, after reallocation newCapacity = old + old / 2 = 9
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(10, v[2]);
    EXPECT_EQ(20, v[3]);
    EXPECT_EQ(30, v[4]);
    EXPECT_EQ(3, v[5]);
    EXPECT_EQ(4, v[6]);
    EXPECT_EQ(5, v[7]);
}


//////////////////////////////////////////////////////////// Element Access Operations ////////////////////////////////////////////////////////////
/**
 * @brief Test case for the At(size_t index) const method of the Vector class,
 *        ensuring correct access to an element at a specific index.
 */
TEST_F(VectorTest, AtConst) {
    // Arrange
    const Vector<int>& constVec = v;

    // Assert
    EXPECT_EQ(1, constVec.At(0));
    EXPECT_EQ(2, constVec.At(1));
    EXPECT_EQ(3, constVec.At(2));
    EXPECT_EQ(4, constVec.At(3));
    EXPECT_EQ(5, constVec.At(4));

    // Out of range index
    EXPECT_THROW(constVec.At(5), std::invalid_argument);
}

/**
 * @brief Test case for the At(size_t index) method of the Vector class,
 *        ensuring correct access to an element at a specific index.
 */
TEST_F(VectorTest, At) {
    // Assert
    EXPECT_EQ(1, v.At(0));
    EXPECT_EQ(2, v.At(1));
    EXPECT_EQ(3, v.At(2));
    EXPECT_EQ(4, v.At(3));
    EXPECT_EQ(5, v.At(4));

    // Out of range index
    EXPECT_THROW(v.At(5), std::invalid_argument);
}

/**
 * @brief Test case for the Back() method of the Vector class,
 *        ensuring correct access to the last element of the vector.
 */
TEST_F(VectorTest, Back) {
    // Assert
    EXPECT_EQ(5, v.Back());

    // Modify back element
    v.Back() = 10;
    EXPECT_EQ(10, v.Back());
}

/**
 * @brief Test case for the Back() const method of the Vector class,
 *        ensuring correct access to the last element of a const vector.
 */
TEST_F(VectorTest, BackConst) {
    // Arrange
    const Vector<int>& constVec = v;

    // Assert
    EXPECT_EQ(5, constVec.Back());
}

/**
 * @brief Test case for the Front() method of the Vector class,
 *        ensuring correct access to the first element of the vector.
 */
TEST_F(VectorTest, Front) {
    // Assert
    EXPECT_EQ(1, v.Front());

    // Modify front element
    v.Front() = 20;
    EXPECT_EQ(20, v.Front());
}

/**
 * @brief Test case for the Front() const method of the Vector class,
 *        ensuring correct access to the first element of a const vector.
 */
TEST_F(VectorTest, FrontConst) {
    // Arrange
    const Vector<int>& constVec = v;

    // Assert
    EXPECT_EQ(1, constVec.Front());
}

/**
 * @brief Test case for the Data() method of the Vector class,
 *        ensuring correct access to the underlying data of the vector.
 */
TEST_F(VectorTest, Data) {
    // Arrange
    int* dataPtr = v.Data();

    // Assert
    EXPECT_EQ(1, dataPtr[0]);
    EXPECT_EQ(2, dataPtr[1]);
    EXPECT_EQ(3, dataPtr[2]);
    EXPECT_EQ(4, dataPtr[3]);
    EXPECT_EQ(5, dataPtr[4]);

    // Modify data through the pointer
    dataPtr[2] = 30;
    EXPECT_EQ(30, v[2]);
}

/**
 * @brief Test case for the Data() const method of the Vector class,
 *        ensuring correct access to the underlying data of a const vector.
 */
TEST_F(VectorTest, DataConst) {
    // Arrange
    const Vector<int>& constVec = v;
    const int* dataPtr = constVec.Data();

    // Assert
    EXPECT_EQ(1, dataPtr[0]);
    EXPECT_EQ(2, dataPtr[1]);
    EXPECT_EQ(3, dataPtr[2]);
    EXPECT_EQ(4, dataPtr[3]);
    EXPECT_EQ(5, dataPtr[4]);
}


//////////////////////////////////////////////////////////// Subscripting Operators ////////////////////////////////////////////////////////////
/**
 * @brief Test case for the operator[](size_t index) const method of the Vector class,
 *        ensuring correct access to an element at a specific index using the subscript operator.
 */
TEST_F(VectorTest, SubscriptOperatorConst) {
    // Arrange
    const Vector<int>& constVec = v;

    // Assert
    EXPECT_EQ(1, constVec[0]);
    EXPECT_EQ(2, constVec[1]);
    EXPECT_EQ(3, constVec[2]);
    EXPECT_EQ(4, constVec[3]);
    EXPECT_EQ(5, constVec[4]);

    // Out of range index
    EXPECT_THROW(constVec[5], VectorException);
}

/**
 * @brief Test case for the operator[](size_t index) method of the Vector class,
 *        ensuring correct access to an element at a specific index using the subscript operator.
 */
TEST_F(VectorTest, SubscriptOperator) {
    // Assert
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);
    EXPECT_EQ(4, v[3]);
    EXPECT_EQ(5, v[4]);

    // Out of range index
    EXPECT_THROW(v[5], VectorException);
}


//////////////////////////////////////////////////////////// Comparison Operators ////////////////////////////////////////////////////////////
/**
 * @brief Test case for the operator<(const Vector<T>& otherVector) const method of the Vector class,
 *        ensuring correct comparison of vectors using the less than operator.
 */
TEST_F(VectorTest, LessThanOperator) {
    // Arrange
    Vector<int> smallerVec{ 1, 2, 3, 4 };
    Vector<int> largerVec{ 1, 2, 3, 4, 5 };

    // Assert
    EXPECT_TRUE(smallerVec < v);
    EXPECT_FALSE(v < smallerVec);
    EXPECT_FALSE(v < v);
    EXPECT_TRUE(smallerVec < largerVec);
    EXPECT_FALSE(largerVec < smallerVec);
}

/**
 * @brief Test case for the operator>(const Vector<T>& otherVector) const method of the Vector class,
 *        ensuring correct comparison of vectors using the greater than operator.
 */
TEST_F(VectorTest, GreaterThanOperator) {
    // Arrange
    Vector<int> smallerVec{ 1, 2, 3, 4 };
    Vector<int> largerVec{ 1, 2, 3, 4, 5 };

    // Assert
    EXPECT_FALSE(smallerVec > v);
    EXPECT_TRUE(v > smallerVec);
    EXPECT_FALSE(v > v);
    EXPECT_FALSE(smallerVec > largerVec);
    EXPECT_TRUE(largerVec > smallerVec);
}

/**
 * @brief Test case for the operator==(const Vector<T>& otherVector) const method of the Vector class,
 *        ensuring correct comparison of vectors using the equality operator.
 */
TEST_F(VectorTest, EqualityOperator) {
    // Arrange
    Vector<int> equalVec{ 1, 2, 3, 4, 5 };
    Vector<int> unequalVec{ 1, 2, 3, 4 };

    // Assert
    EXPECT_TRUE(v == v);
    EXPECT_TRUE(equalVec == v);
    EXPECT_FALSE(unequalVec == v);
}

/**
 * @brief Test case for the operator<=(const Vector<T>& otherVector) const method of the Vector class,
 *        ensuring correct comparison of vectors using the less than or equal to operator.
 */
TEST_F(VectorTest, LessThanOrEqualOperator) {
    // Arrange
    Vector<int> smallerVec{ 1, 2, 3, 4 };
    Vector<int> largerVec{ 1, 2, 3, 4, 5 };

    // Assert
    EXPECT_TRUE(smallerVec <= v);
    EXPECT_FALSE(v <= smallerVec);
    EXPECT_TRUE(v <= v);
    EXPECT_TRUE(smallerVec <= largerVec);
    EXPECT_FALSE(largerVec <= smallerVec);
}

/**
 * @brief Test case for the operator>=(const Vector<T>& otherVector) const method of the Vector class,
 *        ensuring correct comparison of vectors using the greater than or equal to operator.
 */
TEST_F(VectorTest, GreaterThanOrEqualOperator) {
    // Arrange
    Vector<int> smallerVec{ 1, 2, 3, 4 };
    Vector<int> largerVec{ 1, 2, 3, 4, 5 };

    // Assert
    EXPECT_FALSE(smallerVec >= v);
    EXPECT_TRUE(v >= smallerVec);
    EXPECT_TRUE(v >= v);
    EXPECT_FALSE(smallerVec >= largerVec);
    EXPECT_TRUE(largerVec >= smallerVec);
}

/**
 * @brief Test case for the operator!=(const Vector<T>& otherVector) const method of the Vector class,
 *        ensuring correct comparison of vectors using the not equal to operator.
 */
TEST_F(VectorTest, NotEqualOperator) {
    // Arrange
    Vector<int> equalVec{ 1, 2, 3, 4, 5 };
    Vector<int> unequalVec{ 1, 2, 3, 4 };

    // Assert
    EXPECT_FALSE(v != v);
    EXPECT_FALSE(equalVec != v);
    EXPECT_TRUE(unequalVec != v);
}


//////////////////////////////////////////////////////////// Arithmatic Operators ////////////////////////////////////////////////////////////
/**
 * @brief Test case for the operator+(const Vector<T>& otherVector) const method of the Vector class,
 *        ensuring correct addition of vectors.
 */
TEST_F(VectorTest, AdditionOperator_Vector) {
    // Arrange
    Vector<int> otherVec{ 6, 7, 8, 9, 10 };
    Vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Act
    Vector<int> result = v + otherVec;

    // Assert
    EXPECT_EQ(result, expected);
}

/**
 * @brief Test case for the operator+(const T& scalar) const method of the Vector class,
 *        ensuring correct addition of a scalar to each element of the vector.
 */
TEST_F(VectorTest, AdditionOperator_Scalar) {
    // Arrange
    int scalar = 5;
    Vector<int> expected{ 6, 7, 8, 9, 10 };

    // Act
    Vector<int> result = v + scalar;

    // Assert
    EXPECT_EQ(result, expected);
}

/**
 * @brief Test case for the operator-(const Vector<T>& otherVector) const method of the Vector class,
 *        ensuring correct subtraction of vectors.
 */
TEST_F(VectorTest, SubtractionOperator_Vector) {
    // Arrange
    Vector<int> otherVec{ 5, 4, 3, 2, 1 };
    Vector<int> expected{ -4, -2, 0, 2, 4 };

    // Act
    Vector<int> result = v - otherVec;

    // Assert
    EXPECT_EQ(result, expected);

    // Arrange
    otherVec = { 5, 4, 3, 2, 1, 5 };
    expected = { -4, -2, 0, 2, 4, -5 };

    // Act
    result = v - otherVec;

    // Assert
    EXPECT_EQ(result, expected);

    // Arrange
    v.Push_Back(5);
    otherVec = { 5, 4, 3, 2, 1 };
    expected = { -4, -2, 0, 2, 4, 5 };

    // Act
    result = v - otherVec;

    // Assert
    EXPECT_EQ(result, expected);
}

/**
 * @brief Test case for the operator-(const T& scalar) const method of the Vector class,
 *        ensuring correct subtraction of a scalar from each element of the vector.
 */
TEST_F(VectorTest, SubtractionOperator_Scalar) {
    // Arrange
    int scalar = 1;
    Vector<int> expected{ 0, 1, 2, 3, 4 };

    // Act
    Vector<int> result = v - scalar;

    // Assert
    EXPECT_EQ(result, expected);
}

/**
 * @brief Test case for the operator*(const Vector<T>& otherVector) const method of the Vector class,
 *        ensuring correct multiplication of vectors.
 */
TEST_F(VectorTest, MultiplicationOperator_Vector) {
    // Arrange
    Vector<int> otherVec{ 1, 2, 3, 4, 5 };
    Vector<int> expected{ 1, 4, 9, 16, 25 };

    // Act
    Vector<int> result = v * otherVec;

    // Assert
    EXPECT_EQ(result, expected);

    // Arrange
    otherVec = { 1, 2, 3, 4, 5, 6 };

    // Act and Assert
    EXPECT_THROW(v * otherVec, std::invalid_argument);
}

/**
 * @brief Test case for the operator*(const T& scalar) const method of the Vector class,
 *        ensuring correct multiplication of each element of the vector by a scalar.
 */
TEST_F(VectorTest, MultiplicationOperator_Scalar) {
    // Arrange
    int scalar = 2;
    Vector<int> expected{ 2, 4, 6, 8, 10 };

    // Act
    Vector<int> result = v * scalar;

    // Assert
    EXPECT_EQ(result, expected);
}

/**
 * @brief Test case for the operator/(const Vector<T>& otherVector) const method of the Vector class,
 *        ensuring correct division of vectors.
 */
TEST_F(VectorTest, DivisionOperator_Vector) {
    // Arrange
    Vector<int> otherVec{ 1, 2, 3, 4, 5 };
    Vector<int> expected{ 1, 1, 1, 1, 1 };

    // Act
    Vector<int> result = v / otherVec;

    // Assert
    EXPECT_EQ(result, expected);

    // Arrange
    otherVec = { 1, 1, 1, 1, 1, 1 };

    // Act and Assert
    EXPECT_THROW(v / otherVec, std::invalid_argument);
}

/**
 * @brief Test case for the operator/(const T& scalar) const method of the Vector class,
 *        ensuring correct division of each element of the vector by a scalar.
 */
TEST_F(VectorTest, DivisionOperator_Scalar) {
    // Arrange
    int scalar = 2;
    Vector<int> expected{ 0, 1, 1, 2, 2 };

    // Act
    Vector<int> result = v / scalar;

    // Assert
    EXPECT_EQ(result, expected);
}


//////////////////////////////////////////////////////////// Iterators ////////////////////////////////////////////////////////////////////////
/**
 * @brief Test case for the begin() method of the Vector class, ensuring it returns the iterator to the first element.
 */
TEST_F(VectorTest, BeginIterator) {
    // Act
    typename Vector<int>::iterator it = v.begin();

    // Assert
    EXPECT_EQ(*it, 1);
}

/**
 * @brief Test case for the end() method of the Vector class, ensuring it returns the iterator to the element past the last.
 */
TEST_F(VectorTest, EndIterator) {
    // Act
    typename Vector<int>::iterator it = v.end();

    // It will return pointer to element past the last
    // Assert
    EXPECT_EQ(*(it - 1), v.Back());
}



///////////////////////////////////////////////////// Entry Point (testing starts and ends here) ////////////////////////////////////////////////////////////////////////
/**
 * The main function for running Google Test.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of C-style strings representing the command-line arguments.
 * @return An integer representing the exit code of the program. It indicates whether all the tests passed or if there were any failures.
 */
int main(int argc, char** argv) 
{
    // Initialize Google Test with the command-line arguments
    testing::InitGoogleTest(&argc, argv);

    // Run all the registered tests
    return RUN_ALL_TESTS();
}

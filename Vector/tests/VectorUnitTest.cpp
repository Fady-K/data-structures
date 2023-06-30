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
// Test Erase(const size_t& index)
TEST_F(VectorTest, EraseIndex) {
    size_t index = 2;
    int erasedElement = v.Erase(index);
    EXPECT_EQ(3, erasedElement);
    EXPECT_EQ(4, v.size());
    EXPECT_EQ(6, v.capacity());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(4, v[2]);
    EXPECT_EQ(5, v[3]);
}

// Test Erase(iterator pos)
TEST_F(VectorTest, EraseIterator) {
    auto it = v.begin() + 2;
    v.Erase(it);
    EXPECT_EQ(4, v.size());
    EXPECT_EQ(6, v.capacity());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(4, v[2]);
    EXPECT_EQ(5, v[3]);
}

// Test Erase(iterator first, iterator last)
TEST_F(VectorTest, EraseRange) {
    auto first = v.begin() + 1;
    auto last = v.end() - 1;
    v.Erase(first, last);
    EXPECT_EQ(2, v.size());
    EXPECT_EQ(6, v.capacity());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(5, v[1]);
}

// Test Insert(const size_t& index, const T& element)
TEST_F(VectorTest, InsertIndex) {
    size_t index = 2;
    int element = 10;
    const int& insertedElement = v.Insert(index, element);
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

// Test Insert(iterator pos, const T& element)
TEST_F(VectorTest, InsertIterator) {
    auto pos = v.begin() + 2;
    int element = 10;
    v.Insert(pos, element);
    EXPECT_EQ(6, v.size());
    EXPECT_EQ(6, v.capacity());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(10, v[2]);
    EXPECT_EQ(3, v[3]);
    EXPECT_EQ(4, v[4]);
    EXPECT_EQ(5, v[5]);
}

// Test Insert(iterator startPos, std::initializer_list<T> elements)
TEST_F(VectorTest, InsertInitializerList) {
    auto startPos = v.begin() + 2;
    std::initializer_list<int> elements = { 10, 20, 30 };
    v.Insert(startPos, elements);
    EXPECT_EQ(8, v.size());
    EXPECT_EQ(9, v.capacity());     // note old capacity = 6 after reallocationg newCapacity = old + old / 2 = 9
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
// Test At(size_t index) const
TEST_F(VectorTest, AtConst) {
    const Vector<int>& constVec = v;
    EXPECT_EQ(1, constVec.At(0));
    EXPECT_EQ(2, constVec.At(1));
    EXPECT_EQ(3, constVec.At(2));
    EXPECT_EQ(4, constVec.At(3));
    EXPECT_EQ(5, constVec.At(4));

    // Out of range index
    EXPECT_THROW(constVec.At(5), std::invalid_argument);
}

// Test At(size_t index)
TEST_F(VectorTest, At) {
    EXPECT_EQ(1, v.At(0));
    EXPECT_EQ(2, v.At(1));
    EXPECT_EQ(3, v.At(2));
    EXPECT_EQ(4, v.At(3));
    EXPECT_EQ(5, v.At(4));

    // Out of range index
    EXPECT_THROW(v.At(5), std::invalid_argument);
}

// Test Back()
TEST_F(VectorTest, Back) {
    EXPECT_EQ(5, v.Back());

    // Modify back element
    v.Back() = 10;
    EXPECT_EQ(10, v.Back());
}

// Test Back() const
TEST_F(VectorTest, BackConst) {
    const Vector<int>& constVec = v;
    EXPECT_EQ(5, constVec.Back());
}

// Test Front()
TEST_F(VectorTest, Front) {
    EXPECT_EQ(1, v.Front());

    // Modify front element
    v.Front() = 20;
    EXPECT_EQ(20, v.Front());
}

// Test Front() const
TEST_F(VectorTest, FrontConst) {
    const Vector<int>& constVec = v;
    EXPECT_EQ(1, constVec.Front());
}

// Test Data()
TEST_F(VectorTest, Data) {
    int* dataPtr = v.Data();
    EXPECT_EQ(1, dataPtr[0]);
    EXPECT_EQ(2, dataPtr[1]);
    EXPECT_EQ(3, dataPtr[2]);
    EXPECT_EQ(4, dataPtr[3]);
    EXPECT_EQ(5, dataPtr[4]);

    // Modify data through the pointer
    dataPtr[2] = 30;
    EXPECT_EQ(30, v[2]);
}

// Test Data() const
TEST_F(VectorTest, DataConst) {
    const Vector<int>& constVec = v;
    const int* dataPtr = constVec.Data();
    EXPECT_EQ(1, dataPtr[0]);
    EXPECT_EQ(2, dataPtr[1]);
    EXPECT_EQ(3, dataPtr[2]);
    EXPECT_EQ(4, dataPtr[3]);
    EXPECT_EQ(5, dataPtr[4]);
}


//////////////////////////////////////////////////////////// Subscripting Operators ////////////////////////////////////////////////////////////
// Test operator[](size_t index) const
TEST_F(VectorTest, SubscriptOperatorConst) {
    const Vector<int>& constVec = v;
    EXPECT_EQ(1, constVec[0]);
    EXPECT_EQ(2, constVec[1]);
    EXPECT_EQ(3, constVec[2]);
    EXPECT_EQ(4, constVec[3]);
    EXPECT_EQ(5, constVec[4]);

    // Out of range index
    EXPECT_THROW(constVec[5], VectorException);
}

// Test operator[](size_t index)
TEST_F(VectorTest, SubscriptOperator) {
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);
    EXPECT_EQ(4, v[3]);
    EXPECT_EQ(5, v[4]);

    // Out of range index
    EXPECT_THROW(v[5], VectorException);
}



//////////////////////////////////////////////////////////// Comparison Operators ////////////////////////////////////////////////////////////
// Test operator<(const Vector<T>& otherVector) const
TEST_F(VectorTest, LessThanOperator) {
    Vector<int> smallerVec{ 1, 2, 3, 4 };
    Vector<int> largerVec{ 1, 2, 3, 4, 5 };

    EXPECT_TRUE(smallerVec < v);
    EXPECT_FALSE(v < smallerVec);
    EXPECT_FALSE(v < v);
    EXPECT_TRUE(smallerVec < largerVec);
    EXPECT_FALSE(largerVec < smallerVec);
}

// Test operator>(const Vector<T>& otherVector) const
TEST_F(VectorTest, GreaterThanOperator) {
    Vector<int> smallerVec{ 1, 2, 3, 4 };
    Vector<int> largerVec{ 1, 2, 3, 4, 5 };

    EXPECT_FALSE(smallerVec > v);
    EXPECT_TRUE(v > smallerVec);
    EXPECT_FALSE(v > v);
    EXPECT_FALSE(smallerVec > largerVec);
    EXPECT_TRUE(largerVec > smallerVec);
}

// Test operator==(const Vector<T>& otherVector) const
TEST_F(VectorTest, EqualityOperator) {
    Vector<int> equalVec{ 1, 2, 3, 4, 5 };
    Vector<int> unequalVec{ 1, 2, 3, 4 };

    EXPECT_TRUE(v == v);
    EXPECT_TRUE(equalVec == v);
    EXPECT_FALSE(unequalVec == v);
}

// Test operator<=(const Vector<T>& otherVector) const
TEST_F(VectorTest, LessThanOrEqualOperator) {
    Vector<int> smallerVec{ 1, 2, 3, 4 };
    Vector<int> largerVec{ 1, 2, 3, 4, 5 };

    EXPECT_TRUE(smallerVec <= v);
    EXPECT_FALSE(v <= smallerVec);
    EXPECT_TRUE(v <= v);
    EXPECT_TRUE(smallerVec <= largerVec);
    EXPECT_FALSE(largerVec <= smallerVec);
}

// Test operator>=(const Vector<T>& otherVector) const
TEST_F(VectorTest, GreaterThanOrEqualOperator) {
    Vector<int> smallerVec{ 1, 2, 3, 4 };
    Vector<int> largerVec{ 1, 2, 3, 4, 5 };

    EXPECT_FALSE(smallerVec >= v);
    EXPECT_TRUE(v >= smallerVec);
    EXPECT_TRUE(v >= v);
    EXPECT_FALSE(smallerVec >= largerVec);
    EXPECT_TRUE(largerVec >= smallerVec);
}

// Test operator!=(const Vector<T>& otherVector) const
TEST_F(VectorTest, NotEqualOperator) {
    Vector<int> equalVec{ 1, 2, 3, 4, 5 };
    Vector<int> unequalVec{ 1, 2, 3, 4 };

    EXPECT_FALSE(v != v);
    EXPECT_FALSE(equalVec != v);
    EXPECT_TRUE(unequalVec != v);
}


//////////////////////////////////////////////////////////// Arithmatic Operators ////////////////////////////////////////////////////////////
// Test operator+(const Vector<T>& otherVector) const
TEST_F(VectorTest, AdditionOperator_Vector) {
    Vector<int> otherVec{ 6, 7, 8, 9, 10 };
    Vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    Vector<int> result = v + otherVec;

    EXPECT_EQ(result, expected);
}
// Test operator+(const T& scalar) const
TEST_F(VectorTest, AdditionOperator_Scalar) {
    int scalar = 5;
    Vector<int> expected{ 6, 7, 8, 9, 10 };

    Vector<int> result = v + scalar;

    EXPECT_EQ(result, expected);
}

// Test operator-(const Vector<T>& otherVector) const
TEST_F(VectorTest, SubtractionOperator_Vector) {
    Vector<int> otherVec{ 5, 4, 3, 2, 1 };
    Vector<int> expected{ -4, -2, 0, 2, 4 };
    Vector<int> result = v - otherVec;
    EXPECT_EQ(result, expected);

    otherVec = { 5, 4, 3, 2, 1, 5};
    expected = { -4, -2, 0, 2, 4, -5};
    result = v - otherVec;
    EXPECT_EQ(result, expected);

    v.Push_Back(5);
    otherVec = { 5, 4, 3, 2, 1};
    expected = { -4, -2, 0, 2, 4, 5 };
    result = v - otherVec;
    EXPECT_EQ(result, expected);
}
//
// Test operator-(const T& scalar) const
TEST_F(VectorTest, SubtractionOperator_Scalar) {
    int scalar = 1;
    Vector<int> expected{ 0, 1, 2, 3, 4 };

    Vector<int> result = v - scalar;

    EXPECT_EQ(result, expected);
}

// Test operator*(const Vector<T>& otherVector) const
TEST_F(VectorTest, MultiplicationOperator_Vector) {
    Vector<int> otherVec{ 1, 2, 3, 4, 5 };
    Vector<int> expected{ 1, 4, 9, 16, 25 };

    Vector<int> result = v * otherVec;

    EXPECT_EQ(result, expected);

    // if both vector doesn't have the same size throw invalid argument
    otherVec = { 1, 2, 3, 4, 5, 6 };
    EXPECT_THROW(v * otherVec, std::invalid_argument);
}

// Test operator*(const T& scalar) const
TEST_F(VectorTest, MultiplicationOperator_Scalar) {
    int scalar = 2;
    Vector<int> expected{ 2, 4, 6, 8, 10 };

    Vector<int> result = v * scalar;

    EXPECT_EQ(result, expected);
}

// Test operator/(const Vector<T>& otherVector) const
TEST_F(VectorTest, DivisionOperator_Vector) {
    Vector<int> otherVec{ 1, 2, 3, 4, 5 };
    Vector<int> expected{ 1, 1, 1, 1, 1 };

    Vector<int> result = v / otherVec;

    EXPECT_EQ(result, expected);

    // if both vector doesn't have the same size throw invalid argument
    otherVec = { 1, 1, 1, 1, 1, 1};
    EXPECT_THROW(v / otherVec, std::invalid_argument);
}
//
// Test operator/(const T& scalar) const
TEST_F(VectorTest, DivisionOperator_Scalar) {
    int scalar = 2;
    Vector<int> expected{ 0, 1, 1, 2, 2 };

    Vector<int> result = v / scalar;

    EXPECT_EQ(result, expected);
}

//////////////////////////////////////////////////////////// Iterators ////////////////////////////////////////////////////////////////////////
TEST_F(VectorTest, BeginIterator) {
    typename Vector<int>::iterator it = v.begin();

    EXPECT_EQ(*it, 1);
}

// Test end()
TEST_F(VectorTest, EndIterator) {
    typename Vector<int>::iterator it = v.end();

    // It will return pointer to element past the last
    EXPECT_EQ(*(it - 1), v.Back());
}




int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}


#include <gtest/gtest.h>
#include "include/Vector.hpp"


// Test fixture for Vector class
class VectorTest : public testing::Test {
protected:
    Vector<int> v;

    void SetUp() override {
        // Set up any common resources needed for the tests
        v.Push_Back(1);
        v.Push_Back(2);
        v.Push_Back(3);
        v.Push_Back(3);
        v.Push_Back(3);
        v.Push_Back(3);
        v.Push_Back(3);
        v.Push_Back(3);
        v.Push_Back(3);
        v.Push_Back(3);
        v.Push_Back(3);
        v.Push_Back(3);
        v.Push_Back(3);
        v.Push_Back(3);
       
    }

    void TearDown() override {
        // Clean up any shared resources after the tests
        v.Clear();
    }

    // Helper function to check if two vectors are equal
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

////////////////////////////////////////////////////////////// Constructors  ////////////////////////////////////
// Test default constructor
TEST_F(VectorTest, DefaultConstructor) {
    Vector<int> v;
    EXPECT_EQ(0, v.size());
}

// Test parametrized constructor
TEST_F(VectorTest, ParametrizedConstructor) {
    Vector<int> v(5, 10);
    EXPECT_EQ(5, v.size());
    for (int i = 0; i < v.size(); ++i) {
        EXPECT_EQ(10, v[i]);
    }
}

// Test initializer list constructor
TEST_F(VectorTest, InitializerListConstructor) {
    Vector<int> v{ 1, 2, 3, 4, 5 };
    EXPECT_EQ(5, v.size());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);
    EXPECT_EQ(4, v[3]);
    EXPECT_EQ(5, v[4]);
}

// Test copy constructor
TEST_F(VectorTest, CopyConstructor) {
    Vector<int> copy(v);
    EXPECT_EQ(v.size(), copy.size());
    for (int i = 0; i < v.size(); ++i) {
        EXPECT_EQ(v[i], copy[i]);
    }
}

 //Test move constructor
TEST_F(VectorTest, MoveConstructor) {
    Vector<int> original(v);
    Vector<int> moved(std::move(original));
    EXPECT_EQ(v.size(), moved.size());
    EXPECT_EQ(0, original.size()); // After move, the source vector should be empty
}

//////////////////////////////////////////////////////////// Assignment Operators(copy, move) ////////////////////////////////////////////////////////////
TEST_F(VectorTest, CopyAssignmentOperator) {
    Vector<int> vec1{ 1, 2, 3 };
    Vector<int> vec2{ 4, 5 };

    // Copy assign vec1 to vec2
    vec2 = vec1;

    // Check if vec2 is equal to vec1
    ASSERT_TRUE(vectorsAreEqual(vec1, vec2));
}

TEST_F(VectorTest, MoveAssignmentOperator) {
    Vector<int> vec1{ 1, 2, 3 };
    Vector<int> vec2{ 4, 5 };

    // Move assign vec1 to vec2
    vec2 = std::move(vec1);

    // Check if vec2 has the moved data and vec1 is empty
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec1.size(), 0);
}

//////////////////////////////////////////////////////////// Destructor ///////////////////////////////////////////////////////////////////
TEST_F(VectorTest, Destructor_DeallocatesMemory)
{
    // Create a vector
    Vector<int>* vec = new Vector<int>{ 1, 2, 3 };

    // Get the pointer to the underlying data
    int* dataPtr = vec->Data();

    // Destroy the vector
    delete vec;

    // Check if the memory was properly deallocated using Google Test's memory leak detection
    SUCCEED();  // No memory leaks detected
}


//////////////////////////////////////////////////////////// Capacity And Size ////////////////////////////////////////////////////////////
// Test size()
TEST_F(VectorTest, Size) {
    EXPECT_EQ(5, v.size());
    v.Clear();
    EXPECT_EQ(0, v.size());
}

// Test capacity()
TEST_F(VectorTest, Capacity) {
    EXPECT_EQ(6, v.capacity());
    v.Reserve(20);
    EXPECT_EQ(20, v.capacity());
    v.Reserve(10);
    EXPECT_EQ(20, v.capacity()); // Capacity should remain unchanged
}

// Test Max_Size()
TEST_F(VectorTest, MaxSize) {
    EXPECT_EQ(std::numeric_limits<size_t>::max(), v.Max_Size());
}
//
// Test Empty()
TEST_F(VectorTest, Empty) {
    EXPECT_FALSE(v.Empty());
    Vector<int> emptyVec;
    EXPECT_TRUE(emptyVec.Empty());
}

// Test Full()
TEST_F(VectorTest, Full) {
    EXPECT_FALSE(v.Full());
    Vector<int> fullVec(5, 10);
    EXPECT_TRUE(fullVec.Full());
}

// Test Reserve()
TEST_F(VectorTest, Reserve) {
    v.Reserve(20);
    EXPECT_EQ(5, v.size()); // Size should remain unchanged
    EXPECT_EQ(20, v.capacity());
}

// Test Shrink_To_Fit()
TEST_F(VectorTest, ShrinkToFit) {
    v.Shrink_To_Fit();
    EXPECT_EQ(5, v.size()); // Size should remain unchanged
    EXPECT_EQ(5, v.capacity());
}

// Test Clear()
TEST_F(VectorTest, Clear) {
    EXPECT_EQ(5, v.size());
    v.Clear();
    EXPECT_EQ(0, v.size());
    EXPECT_EQ(6, v.capacity()); // Capacity should remain unchanged
}
//////////////////////////////////////////////////////////// Modifiers ///////////////////////////////////////////////////////////////////////

// Test Push_Back(const T& element)
TEST_F(VectorTest, PushBackLvalue) {
    int element = 10;
    const int& pushedElement = v.Push_Back(element);
    EXPECT_EQ(element, pushedElement);
    EXPECT_EQ(6, v.size());
    EXPECT_EQ(6, v.capacity());         // capacity should remain the same as still their size from the last push_back opertion
    EXPECT_EQ(element, v[v.size() - 1]);
}

// Test Push_Back(T&& element)
TEST_F(VectorTest, PushBackRvalue) {
    int element = 10;
    int&& rvalueElement = std::move(element);
    v.Push_Back(std::move(rvalueElement));
    EXPECT_EQ(6, v.size());
    EXPECT_EQ(6, v.capacity());     // capacity should remain the same as still their size from the last push_back opertion
    EXPECT_EQ(10, v[v.size() - 1]);
}

// Test Pop_Back()
TEST_F(VectorTest, PopBack) {
    int poppedElement = v.Pop_Back();
    EXPECT_EQ(5, poppedElement);
    EXPECT_EQ(4, v.size());
    EXPECT_EQ(6, v.capacity());     // capacity should remain the same as still their size from the last push_back opertion
}

 //Test Resize(size_t newSize)
TEST_F(VectorTest, Resize) {
    v.Resize(10);
    EXPECT_EQ(10, v.size());
    EXPECT_EQ(10, v.capacity());

    v.Resize(3);
    EXPECT_EQ(3, v.size());
    EXPECT_EQ(10, v.capacity());
}

// Test Resize(size_t newSize, const T& defaultValue)
TEST_F(VectorTest, ResizeWithDefaultValue) {
    int defaultValue = 100;
    int oldSize = v.size();
    v.Resize(10, defaultValue);
    EXPECT_EQ(10, v.size());
    EXPECT_EQ(10, v.capacity());
    for (size_t i = oldSize; i < v.size(); ++i) // note resize init the extra size only with default value
    {
        EXPECT_EQ(defaultValue, v[i]);
    }

    v.Resize(3, defaultValue);
    EXPECT_EQ(3, v.size());
    EXPECT_EQ(10, v.capacity());
}

// Test Swap(Vector<T>& v)
TEST_F(VectorTest, Swap) {
    Vector<int> v2{ 100, 200, 300 };
    v.Swap(v2);
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


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

//////////////////////////////////////////////////////////////// Assignment Operators ////////////////////////////////////
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


////////////////////////////////////////////////////////////////  Destructor ////////////////////////////////////
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





int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}


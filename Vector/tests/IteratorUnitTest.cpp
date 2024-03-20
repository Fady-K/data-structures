/**
 * @file IteratorUnitTest.cpp
 * @author Fady Kamal (popfadykamal151617@gmail.com)
 * @brief Unit tests for Iterator class
 * @date 2023-07-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../Iterator/Iterator.hpp"  // Include the header file for the Iterator class
#include <gtest/gtest.h>  // Include the Google Test framework

/**
 * @brief Test fixture class for the Iterator tests
 */
class IteratorTest : public ::testing::Test {
protected:
    Iterator<int> it; /**< Member variable for the Iterator object */
};

/**
 * @brief Test case for the default constructor
 */
TEST_F(IteratorTest, DefaultConstructor) {
    // Test that the default constructor creates an Iterator with a null pointer
    EXPECT_EQ(nullptr, it.getCurrentPointer());
}

/**
 * @brief Test case for the parametrized constructor
 */
TEST_F(IteratorTest, ParametrizedConstructor) {
    int value = 42;
    Iterator<int> it(&value);

    // Test that the parametrized constructor sets the current pointer correctly
    EXPECT_EQ(&value, it.getCurrentPointer());
}

/**
 * @brief Test case for the copy constructor
 */
TEST_F(IteratorTest, CopyConstructor) {
    int value = 42;
    Iterator<int> it1(&value);
    Iterator<int> it2(it1);

    // Test that the copy constructor creates a new Iterator with the same current pointer
    EXPECT_EQ(it1.getCurrentPointer(), it2.getCurrentPointer());
}

/**
 * @brief Test case for the move constructor
 */
TEST_F(IteratorTest, MoveConstructor) {
    int value = 42;
    Iterator<int> it1(&value);
    Iterator<int> it2(std::move(it1));

    // Test that the move constructor transfers the current pointer correctly
    EXPECT_EQ(&value, it2.getCurrentPointer());
    EXPECT_EQ(nullptr, it1.getCurrentPointer());
}

/**
 * @brief Test case for the copy assignment operator
 */
TEST_F(IteratorTest, CopyAssignmentOperator) {
    int value = 42;
    Iterator<int> it1(&value);
    Iterator<int> it2;
    it2 = it1;

    // Test that the copy assignment operator copies the current pointer correctly
    EXPECT_EQ(it1.getCurrentPointer(), it2.getCurrentPointer());
}

/**
 * @brief Test case for the move assignment operator
 */
TEST_F(IteratorTest, MoveAssignmentOperator) {
    int value = 42;
    Iterator<int> it1(&value);
    Iterator<int> it2;
    it2 = std::move(it1);

    // Test that the move assignment operator transfers the current pointer correctly
    EXPECT_EQ(&value, it2.getCurrentPointer());
    EXPECT_EQ(nullptr, it1.getCurrentPointer());
}

/**
 * @brief Test case for the dereference operator
 */
TEST_F(IteratorTest, DereferenceOperator) {
    int value = 42;
    it.setCurrentPointer(&value);

    // Test that the dereference operator returns the correct value
    EXPECT_EQ(value, *it);
}

/**
 * @brief Test case for the arrow operator
 */
TEST_F(IteratorTest, ArrowOperator) {
    int value = 42;
    it.setCurrentPointer(&value);

    // Test that the arrow operator returns the correct pointer
    EXPECT_EQ(&value, it.operator->());
}

/**
 * @brief Test case for the pre-increment operator
 */
TEST_F(IteratorTest, PreIncrementOperator) {
    // Create an iterator with a valid pointer
    int arr[] = { 1, 2, 3 };
    Iterator<int> it(&arr[0]);

    // Apply the pre-increment operator
    ++it;

    // Test that the current pointer is incremented correctly
    EXPECT_EQ(&arr[1], it.getCurrentPointer());

}

/**
 * @brief Test case for the post-increment operator
 */
TEST_F(IteratorTest, PostIncrementOperator) {
    int arr[] = { 1, 2, 3 };
    Iterator<int> it(&arr[0]);

    // Apply the post-increment operator
    Iterator<int> result = it++;

    // Test that the post-increment operator returns the expected iterator before the increment
    EXPECT_EQ(&arr[0], result.getCurrentPointer());

    // Test that the current pointer is incremented correctly
    EXPECT_EQ(&arr[1], it.getCurrentPointer());
}


// Add more test cases for other member functions of the Iterator class...

/**
 * @brief Main function to run the tests
 * @param argc Number of command-line arguments
 * @param argv Command-line argument values
 * @return Test result
 */
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

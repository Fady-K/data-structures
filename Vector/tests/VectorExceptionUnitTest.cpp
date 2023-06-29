#include <gtest/gtest.h>
#include "../exceptions/VectorException.hpp"

// Test fixture class
class VectorExceptionTest : public ::testing::Test {
protected:
    VectorException exception;

    void SetUp() override {
        exception.SetMsg("Test exception message");
    }
};

// Test case for default constructor
TEST_F(VectorExceptionTest, DefaultConstructor) {
    VectorException defaultException;
    EXPECT_STREQ("", defaultException.what());
}

// Test case for parametrized constructor
TEST_F(VectorExceptionTest, ParametrizedConstructor) {
    EXPECT_STREQ("Test exception message", exception.what());
}

// Test case for copy constructor
TEST_F(VectorExceptionTest, CopyConstructor) {
    VectorException original("Original error");
    VectorException copy(original);
    EXPECT_STREQ(original.what(), copy.what());
}

// Test case for copy assignment operator
TEST_F(VectorExceptionTest, CopyAssignmentOperator) {
    VectorException original("Original error");
    VectorException assigned;
    assigned = original;
    EXPECT_STREQ(original.what(), assigned.what());
}

// Test case for GetMsg() method
TEST_F(VectorExceptionTest, GetMsg) {
    EXPECT_EQ("Test exception message", exception.GetMsg());
}

// Test case for SetMsg() method
TEST_F(VectorExceptionTest, SetMsg) {
    exception.SetMsg("New exception message");
    EXPECT_EQ("New exception message", exception.GetMsg());
}

// Test case for exception handling
TEST_F(VectorExceptionTest, ExceptionHandling) {
    try {
        throw exception;
    }
    catch (const VectorException& e) {
        EXPECT_STREQ("Test exception message", e.what());
    }
}

// Main function to run the tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
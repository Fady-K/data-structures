/**
 * @file VectorExceptionUnitTest.cpp
 * @author Fady Kamal (popfadykamal151617@gmail.com)
 * @brief This file contains unit testing of the VectorException class.
 * @details It includes test cases for the constructors, assignment operator,
 * getters, setters, and exception handling of the VectorException class.
 * @date 2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <gtest/gtest.h>
#include "../exceptions/VectorException.hpp"

/**
 * @brief Test fixture class for VectorException.
 * @details Provides a common setup and resources for the test cases.
 */
class VectorExceptionTest : public ::testing::Test 
{
protected:
    VectorException exception;  /**< VectorException object for testing */

    /**
     * @brief Setup method called before each test case.
     * @details Sets up the error message for the VectorException object.
     */
    void SetUp() override 
    {
        exception.SetMsg("Test exception message");
    }
};

/**
 * @test Test the default constructor of VectorException.
 * @details Verifies that the default-constructed VectorException object has an
 * empty error message.
 */
TEST_F(VectorExceptionTest, DefaultConstructor) 
{
    VectorException defaultException;
    EXPECT_STREQ("", defaultException.what());
}

/**
 * @test Test the parametrized constructor of VectorException.
 * @details Verifies that the VectorException object created with a given error
 * message returns the same message when queried.
 */
TEST_F(VectorExceptionTest, ParametrizedConstructor) 
{
    EXPECT_STREQ("Test exception message", exception.what());
}

/**
 * @test Test the copy constructor of VectorException.
 * @details Verifies that the copy-constructed VectorException object has the
 * same error message as the original object.
 */
TEST_F(VectorExceptionTest, CopyConstructor) 
{
    VectorException original("Original error");
    VectorException copy(original);
    EXPECT_STREQ(original.what(), copy.what());
}

/**
 * @test Test the copy assignment operator of VectorException.
 * @details Verifies that the VectorException object assigned from another object
 * has the same error message as the original object.
 */
TEST_F(VectorExceptionTest, CopyAssignmentOperator) 
{

    VectorException original("Original error");
    VectorException assigned;
    assigned = original;
    EXPECT_STREQ(original.what(), assigned.what());
}

/**
 * @test Test the GetMsg() method of VectorException.
 * @details Verifies that the GetMsg() method returns the correct error message
 * stored in the VectorException object.
 */
TEST_F(VectorExceptionTest, GetMsg) 
{

    EXPECT_EQ("Test exception message", exception.GetMsg());
}

/**
 * @test Test the SetMsg() method of VectorException.
 * @details Verifies that the SetMsg() method successfully updates the error
 * message of the VectorException object.
 */
TEST_F(VectorExceptionTest, SetMsg) 
{

    exception.SetMsg("New exception message");
    EXPECT_EQ("New exception message", exception.GetMsg());
}

/**
 * @test Test the exception handling of VectorException.
 * @details Verifies that when a VectorException is thrown and caught, the error
 * message in the caught exception matches the original error message.
 */
TEST_F(VectorExceptionTest, ExceptionHandling) 
{
    try {
        throw exception;
    }
    catch (const VectorException& e) {
        EXPECT_STREQ("Test exception message", e.what());
    }
}


/**
 * @brief Main function to run the unit tests for VectorException class.
 *
 * This function initializes the Google Test framework, runs all the tests defined in the test cases,
 * and returns the exit code indicating the test results.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return int The exit code indicating the test results.
 */
int main(int argc, char** argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
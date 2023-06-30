#pragma once
#include <iostream>
#include <exception>
#include <string>

/**
 * @class VectorException
 * @brief Exception class for the Vector class.
 */
class VectorException : public std::exception
{
protected:
    std::string m_Msg; /**< The error message. */

public:
    /**
     * @brief Default constructor.
     */
    VectorException() noexcept;

    /**
     * @brief Constructor with a custom error message.
     * @param t_Msg The error message.
     */
    explicit VectorException(const std::string& t_Msg) noexcept;

    /**
     * @brief Copy constructor.
     * @param otherVector The VectorException object to copy.
     */
    VectorException(const VectorException& otherVector) noexcept;

    /**
     * @brief Assignment operator.
     * @param otherVector The VectorException object to assign.
     * @return Reference to the assigned VectorException object.
     */
    VectorException& operator=(const VectorException& otherVector) noexcept;

    /**
     * @brief Destructor.
     */
    ~VectorException() override;

    /**
     * @brief Sets the error message.
     * @param m_Msg The error message to set.
     */
    void SetMsg(const std::string& m_Msg) noexcept;

    /**
     * @brief Gets the error message.
     * @return The error message.
     */
    const std::string& GetMsg() const noexcept;

    /**
     * @brief Returns the error message as a C-style string.
     * @return The error message as a C-style string.
     */
    const char* what() const noexcept override;
};




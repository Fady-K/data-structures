#pragma once
#include <iostream>
#include <exception>
#include <string>

class VectorException: public std::exception
{
    /* Instane Attributes */
protected:
    std::string m_Msg;
    

    /* Instance Methods*/
public:
    explicit VectorException() noexcept;                                                 // default constructor
    VectorException(const std::string& t_Msg) noexcept;                                  // parametrized constructor
    VectorException(const VectorException& otherException) noexcept;                     // default copy constructor
    VectorException& operator=(const VectorException& otherException) noexcept;          // copy assignment operator
    ~VectorException() noexcept;                                                         // destructor

    /* Setters and Getters */
    void SetMsg(const std::string& t_Msg) noexcept;
    const std::string& GetMsg() const noexcept;

    // what
    virtual const char* what() const noexcept override;
};



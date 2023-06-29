#include "VectorException.hpp"

//////////////////////////////////////////////// Constructors ///////////////////////////////////////////////
VectorException::VectorException() noexcept : m_Msg(""){}

VectorException::VectorException(const std::string& t_Msg) noexcept : m_Msg(t_Msg){}

VectorException::VectorException(const VectorException& otherVector) noexcept : m_Msg(otherVector.m_Msg){}

//////////////////////////////////////////////// Assighment Operators ///////////////////////////////////////////////
VectorException& VectorException::operator=(const VectorException& otherVector) noexcept
{
    // if not equvalnt copy else returh *this
    if (this != &otherVector)
    {
        this->m_Msg = otherVector.m_Msg;
    }

    return *this;    
}


//////////////////////////////////////////////// Destructor ///////////////////////////////////////////////
VectorException::~VectorException(){}

//////////////////////////////////////////////// Setters and Getters ///////////////////////////////////////////////
void VectorException::SetMsg(const std::string& m_Msg) noexcept
{
    this->m_Msg = m_Msg;
}


const std::string& VectorException::GetMsg() const noexcept
{
    return this->m_Msg;    
}


const char* VectorException::what() const noexcept
{
    return this->m_Msg.c_str();
}
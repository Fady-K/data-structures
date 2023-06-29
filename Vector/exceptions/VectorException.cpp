#include "VectorException.hpp"

//////////////////////////////////////////////// Constructors ///////////////////////////////////////////////
VectorException::VectorException(): m_Msg(""){}

VectorException::VectorException(const std::string& t_Msg): m_Msg(t_Msg){}

VectorException::VectorException(const VectorException& otherVector): m_Msg(otherVector.m_Msg){}

//////////////////////////////////////////////// Assighment Operators ///////////////////////////////////////////////
VectorException& VectorException::operator=(const VectorException& otherVector)
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
void VectorException::SetMsg(const std::string& m_Msg)
{
    this->m_Msg = m_Msg;
}


const std::string& VectorException::GetMsg() const
{
    return this->m_Msg;    
}


const char* VectorException::what() const noexcept
{
    return this->m_Msg.c_str();
}
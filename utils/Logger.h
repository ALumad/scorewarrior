#pragma once
#include <string>
#include <sstream>
class Logger {
public:
    std::string Log() {
        return m_ss.str();
    }
    template<class T>
    Logger& Append(const T& value){
        m_ss << value;   
        return *this;
    }
    template<class T> 
    Logger& 
    operator << (const T& value) {
        return Append(value);
    }

    void Clear()  {
        m_ss.str("");
        m_ss.clear();
    }
private: 
    std::stringstream m_ss;
};
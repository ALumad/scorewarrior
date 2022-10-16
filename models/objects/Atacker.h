#pragma once
#include "Object.h"
class Atacker : public Object {
public:    
    Atacker(const std::size_t& id, const std::size_t& strength): 
        Object(id), m_strength(strength){}
    
    std::size_t Atack() { return m_strength;}
protected:
    std::size_t m_strength;    
};
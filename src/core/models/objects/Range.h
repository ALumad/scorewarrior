#pragma once 
#include "Atacker.h"


class Range :  public Atacker {
public:
    Range(const std::size_t& id, const std::size_t& strength, const std::size_t& distance): 
        Atacker(id, strength), m_distance(distance) {}
    
    std::size_t GetDistance() {return m_distance;}
private:
    std::size_t m_distance = 1;
    
};
#pragma once
#include "Atacker.h"
class Warrior : public Atacker {
public:    
    Warrior(const std::size_t& id, const std::size_t& strength): 
        Atacker(id, strength){}
};
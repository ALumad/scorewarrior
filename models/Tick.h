#pragma once
#include "utils/Signleton.h"

class Tick final: public Singleton<Tick> {
public:
    void AddTicks(const std::size_t& tick);
    std::size_t GetTicks();
private:
    std::size_t m_tick = 0;
};
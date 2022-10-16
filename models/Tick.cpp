#include "Tick.h"

void Tick::AddTicks(const std::size_t& tick) {
    m_tick += tick;
}
std::size_t Tick::GetTicks() {
    return m_tick;
}
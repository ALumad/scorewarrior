#include "Map.h"
#include <iostream>
void Map::initialize(const std::size_t& width, const std::size_t& height) {
    m_field.resize(height);
    for (auto& l: m_field){
        l.resize(width, 0);
    }
}
std::size_t& Map::operator[] (const Point& p){
    return m_field[p.y][p.x];
}
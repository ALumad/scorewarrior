#pragma once
#include <vector>
#include "utils/Signleton.h"
#include "utils/Point.h"

class Map final: public Singleton<Map> {
public:
    void initialize(const std::size_t& width, const std::size_t& height);
    std::size_t& operator[] (const Point& p);
private:
    std::vector<std::vector<std::size_t>> m_field;
};
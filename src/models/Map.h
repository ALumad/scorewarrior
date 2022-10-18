#pragma once
#include <vector>
#include <utility>
#include "utils/Signleton.h"
#include "utils/Point.h"

class Map final: public Singleton<Map> {
public:
    void initialize(const std::size_t& width, const std::size_t& height);
    std::size_t& operator[] (const Point& p);
    std::pair<std::size_t, std::size_t> GetSize();
private:
    std::vector<std::vector<std::size_t>> m_field;
};
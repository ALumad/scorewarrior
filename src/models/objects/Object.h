#pragma once
#include <cstdlib>
class Object {
public:
    Object(const std::size_t& id): m_id(id) {}
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
    std::size_t GetId() {return m_id;}
    virtual ~Object() = default;
private:
    std::size_t m_id;   
};


#pragma once
#include "utils/Signleton.h"
#include "utils/Point.h"
#include "models/objects/Object.h"
#include <unordered_map>
#include <memory>
#include "utils/Point.h"
class Controller : public Singleton<Controller> {
public:

    std::shared_ptr<Object> GetObject(const Point& p);
    std::shared_ptr<Object> GetObject(const std::size_t& id);
    void PutObject(std::shared_ptr<Object>& obj,const Point& p);
    void DropObject(const std::size_t& id);
    void MoveObject(const std::size_t& id, const Point& to);

    void CreateMap(const std::size_t& width, const std::size_t& height);
    std::size_t TickToPoint(const std::size_t& id,const Point& p);
    int Battle(const std::size_t& id1, const std::size_t& id2);

private:
    std::unordered_map<std::size_t, std::shared_ptr<Object>> m_id2object;
    std::unordered_map<std::size_t, Point> m_id2point;
};
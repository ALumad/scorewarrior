#pragma once
#include "utils/Singleton.h"
#include "utils/Point.h"
#include "models/objects/Object.h"
#include <unordered_map>
#include <memory>
#include "utils/Point.h"
#include "set"
class Controller : public Singleton<Controller>{
public:

    std::shared_ptr<Object> GetObject(const Point& p);
    std::shared_ptr<Object> GetObject(const std::size_t& id);
    void PutObject(std::shared_ptr<Object>& obj,const Point& p);
    void DropObject(const std::size_t& id);

    void StartMoveObject(const std::size_t& id);
    void EndMoveObject(const std::size_t& id, const Point& to);

    void CreateMap(const std::size_t& width, const std::size_t& height);
    std::size_t TickToPoint(const std::size_t& id,const Point& p);
    Point GetObjectPosition(const std::size_t& id);
    Point GetObjectPrevPosition(const std::size_t& id);

    std::size_t FirstCloseObject(const std::size_t& id);
protected:

    std::unordered_map<std::size_t, std::shared_ptr<Object>> m_id2object;
    std::unordered_map<std::size_t, Point> m_id2point;
    std::unordered_map<std::size_t, Point> m_id2point_in_move;
};
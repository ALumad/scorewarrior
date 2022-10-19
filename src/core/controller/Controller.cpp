#include <math.h>
#include "Controller.h"
#include "models/Map.h"
#include "utils/Point.h"
#include "models/objects/Atacker.h"
#include "models/objects/Range.h"
#include <sstream>
std::shared_ptr<Object> Controller::GetObject(const Point& p) {
    std::size_t id = Singleton<Map>::instance()[p];
    if (id == 0)
        return nullptr;
    return GetObject(id);

}
std::shared_ptr<Object> Controller::GetObject(const std::size_t& id) {
    return m_id2object[id];
}

void Controller::PutObject(std::shared_ptr<Object>& obj,const Point& p) {
    auto hw_size = Singleton<Map>::instance().GetSize();
    if (p.x >= hw_size.first || p.y >= hw_size.second) {
        std::stringstream ss;
        ss << "Point " << p.x << " " << p.y << " not in map";
        throw std::out_of_range(ss.str());
    }
    m_id2object[obj->GetId()] = obj;
    m_id2point[obj->GetId()] = p;
    Singleton<Map>::instance()[p] = obj->GetId();
}

void Controller::DropObject(const std::size_t& id) {
    auto p = m_id2point[id];
    Singleton<Map>::instance()[p] = 0;
    m_id2object.erase(id);
    m_id2point.erase(id);
}


void Controller::CreateMap(const std::size_t& width, const std::size_t& height){
    Singleton<Map>::instance().initialize(width,height);    
}

std::size_t Controller::TickToPoint(const std::size_t& id,const Point& p){
    Point ps = m_id2point[id];
    auto res = sqrt( (p.x-ps.x)*(p.x-ps.x) + (p.y-ps.y)*(p.y-ps.y));
    return static_cast<std::size_t>(res);
}

void Controller::EndMoveObject(const std::size_t& id, const Point& to){
    Singleton<Map>::instance()[to] = id;
    m_id2point[id] = to;
    m_id2point_in_move.erase(id);
}

Point Controller::GetObjectPosition(const std::size_t& id){
    return m_id2point[id];
}

Point Controller::GetObjectPrevPosition(const std::size_t& id) {
     return m_id2point_in_move[id];   
}

void Controller::StartMoveObject(const std::size_t& id) {
    auto p = m_id2point[id];
    Singleton<Map>::instance()[p] = 0;
    m_id2point_in_move[id] = p;
    m_id2point.erase(id);
}


std::size_t Controller::FirstCloseObject(const std::size_t& id) {
    auto range = dynamic_cast<Range*>(m_id2object[id].get());
    if (!range) return 0;
    for (auto& p : m_id2point){
        if (p.first == id) continue;
        if (TickToPoint(id, p.second) <= range->GetDistance()) return p.first;
    }
    return  0;
}
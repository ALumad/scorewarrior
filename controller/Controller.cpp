#include <math.h>
#include "Controller.h"
#include "models/Map.h"
#include "utils/Point.h"
#include "models/objects/Atacker.h"
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


int Controller::Battle(const std::size_t& id1, const std::size_t& id2){
    auto ptr1 = m_id2object[id1].get();
    auto ptr2 = m_id2object[id2].get();
    int res =  dynamic_cast<Atacker*>(ptr1)->Atack() - dynamic_cast<Atacker*>(ptr2)->Atack();
    if (res < 0) {
        return res;
    } else if (res > 0) {
        DropObject(id2);
    }
    else {
        DropObject(id1);
        DropObject(id2);
    }
    return res;
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
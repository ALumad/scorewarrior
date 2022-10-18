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


int Controller::Battle(const std::size_t& id1, const std::size_t& id2){
    auto ptr1 = m_id2object[id1].get();
    auto ptr2 = m_id2object[id2].get();
    int res = 0;
    if (dynamic_cast<Range*>(ptr1) || dynamic_cast<Range*>(ptr1)) {
        res = DistanceBattle(id1, id2);
    } else {
        res =  dynamic_cast<Atacker*>(ptr1)->Atack() - dynamic_cast<Atacker*>(ptr2)->Atack();
    }
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

int Controller::DistanceBattle(const std::size_t& id1, const std::size_t& id2) {
    auto warrior1 = dynamic_cast<Atacker*>(m_id2object[id1].get());
    auto warrior2 = dynamic_cast<Atacker*>(m_id2object[id2].get());

    auto range1 = dynamic_cast<Range*>(m_id2object[id1].get());
    auto range2 = dynamic_cast<Range*>(m_id2object[id2].get());    
    int res = 0;

    if (range1 && range2){
        if (range1->GetDistance() == range2->GetDistance())
            return range1->Atack() - range2->Atack();
        else if (range1->GetDistance() < range2->GetDistance()) {
            return -1;
        }
        else {
            if (range1->Atack() >= range2->Atack()) return 1;
            return -1;
        }
    }
    else if (range1) {
        if (range1->Atack() >= warrior2->Atack()) return 1;
        return -1;        
    } else {
        if (range2->Atack() >= warrior1->Atack()) return -1;
        return 1;        
    }
    return 0; //Will never happend
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
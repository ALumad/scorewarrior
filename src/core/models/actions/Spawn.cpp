#include "Spawn.h"
#include "models/Tick.h"
#include <sstream>
#include <iostream>
#include "controller/Controller.h"
#include "models/objects/Warrior.h"
#include "models/objects/Range.h"
#include "models/Map.h"
IAction::Result SpawnAction::Do(){
    if (m_status != IAction::STATUS::WAITING)
        return {m_status, "", false};
    m_start_tick = Singleton<Tick>::instance().GetTicks();
    m_status = IAction::STATUS::SUCCESS;
    m_end_tick = Singleton<Tick>::instance().GetTicks();
    CreateAndStore();
    std::string msg = Log();
    m_log.Clear();
    return {m_status,msg};
}

void SpawnAction::SetId(const std::size_t& id){
    m_id = id;
}
void SpawnAction::SetPosition(const Point& p) {
    m_position = p;
}
void SpawnAction::SetStrength(const std::size_t& strength){
    m_strength = strength;
}

std::string SpawnAction::Log() {
    m_log << "[" << m_end_tick << "] " << "WARRIOR SPAWNED " 
        << m_id << " ON " << m_position.x << " " << m_position.y;
    std::string res = m_log.Log();    
    return res;
}

void SpawnAction::CreateAndStore(){
    auto ptr = std::shared_ptr<Object>(new Warrior(m_id, m_strength));
    try {
        Singleton<Controller>::instance().PutObject(ptr,m_position);
    } catch(std::out_of_range& e){
        std::cout << e.what() << std::endl;
        exit(0);
    }
    
}

void SpawnRangeAction::CreateAndStore() {
    auto ptr = std::shared_ptr<Object>(new Range(m_id, m_strength, m_distance));
    try {
        Singleton<Controller>::instance().PutObject(ptr,m_position);
    } catch(std::out_of_range& e){
        std::cout << e.what() << std::endl;
        exit(0);
    }    
}

void SpawnRangeAction::SetDistance(const std::size_t& distance) {
    m_distance = distance;
}

std::string SpawnRangeAction::Log() {
    m_log << "[" << m_end_tick << "] " << "ARCHER SPAWNED " 
        << m_id << " ON " << m_position.x << " " << m_position.y;
    std::string res = m_log.Log();    
    return res;
}
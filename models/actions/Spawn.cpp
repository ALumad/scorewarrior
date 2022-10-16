#include "Spawn.h"
#include "models/Tick.h"
#include <sstream>
#include <iostream>
#include "controller/Controller.h"
#include "models/objects/Warrior.h"
#include "models/Map.h"
IAction::STATUS SpawnAction::Do(){
    if (m_status != IAction::STATUS::WAITING)
        return m_status;
    m_start_tick = Singleton<Tick>::instance().GetTicks();
    m_status = IAction::STATUS::SUCCESS;
    m_end_tick = Singleton<Tick>::instance().GetTicks();
    CreateAndStore();
    std::cout << Log() << std::endl;
    return m_status;
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
    Singleton<Controller>::instance().PutObject(ptr,m_position);
    
}
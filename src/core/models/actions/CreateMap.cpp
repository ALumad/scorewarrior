#include "CreateMap.h"
#include <cstddef>
#include "controller/Controller.h"
#include "models/Tick.h"
#include <sstream>
#include <iostream>

CreateMapAction::CreateMapAction(const std::size_t& width, const std::size_t& height)
: m_width(width), m_height(height) 
{

}

bool CreateMapAction::Check() {
    return (m_width > 0 && m_height > 0);
}

void CreateMapAction::SetMapSize(const std::size_t& width, const std::size_t& height){
    m_width = width;
    m_height = height;
}

IAction::STATUS CreateMapAction::Do(){
    if (m_status != IAction::STATUS::WAITING)
        return m_status;
    m_start_tick = Singleton<Tick>::instance().GetTicks();
    Singleton<Controller>::instance().CreateMap(m_width,m_height);
    m_status = IAction::STATUS::SUCCESS;
    m_end_tick = Singleton<Tick>::instance().GetTicks();
    std::cout << Log() << std::endl;
    return m_status;
}

std::string CreateMapAction::Log() {
    m_log << "[" << m_end_tick << "] " << "MAP CREATED " << m_width << " " << m_height;
    return m_log.Log();
}
#include "March.h"
#include "models/Tick.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "controller/Controller.h"
IAction::STATUS MarchAction::Do() {
    if ( m_status == IAction::STATUS::WAITING) {
        return DoWaitingInprogress();
    } else if (m_status == IAction::STATUS::INPROGRESS 
            && Singleton<Tick>::instance().GetTicks() >= m_end_tick) {
        return DoInprogressSuccess();
    }
    return m_status;
}

IAction::STATUS MarchAction::DoWaitingInprogress() {
    if ( m_status != IAction::STATUS::WAITING) return m_status;
    m_start_tick = (m_is_backward ? m_end_tick : Singleton<Tick>::instance().GetTicks());
    m_status = IAction::STATUS::INPROGRESS;
    auto tick = Singleton<Controller>::instance().TickToPoint(m_id,m_point);
    m_end_tick= m_start_tick+tick;
    Singleton<Controller>::instance().StartMoveObject(m_id);
    m_log << "[" << m_start_tick << "] "
        << "MARCH STARTED " << m_id 
        << " TO " << m_point.x << " " << m_point.y;
    std::cout << m_log.Log() << std::endl;
    m_log.Clear();
    return m_status;   
}
IAction::STATUS MarchAction::DoInprogressSuccess(){
    if (m_status != IAction::STATUS::INPROGRESS 
      || Singleton<Tick>::instance().GetTicks() < m_end_tick) return m_status;
    m_status = IAction::STATUS::SUCCESS;
    m_log << "[" << m_end_tick << "] "
           << "MARCH " <<  m_id 
           << " FINISHED " << m_point.x << " " << m_point.y;
    Point prev_pos = Singleton<Controller>::instance().GetObjectPrevPosition(m_id);
    auto ptr = Singleton<Controller>::instance().GetObject(m_point);
    Singleton<Controller>::instance().EndMoveObject(m_id, m_point);
    if (ptr.get()) {
        std::size_t id = ptr->GetId();
        int battle_res = Singleton<Controller>::instance().Battle(m_id, id);
        m_log << " BATTLE " << std::min(m_id,id) 
                << " " << std::max(m_id,id);
          
        if (battle_res == 0){
            m_log << " ALL DEAD";
        }
        else if (battle_res < 0) {
            m_log << " WINNERS IS " << id;
            m_status = IAction::STATUS::WAITING;
            m_point = prev_pos;
            m_is_backward = true;
        } else {
            m_log << " WINNERS IS " << m_id;
        }
    }
    std::cout << m_log.Log() << std::endl;
    m_log.Clear();
    return m_status;
}

void MarchAction::SetId(const std::size_t& id) {
    m_id = id;
}
void MarchAction::SetPosition(const Point& p) {
    m_point = p;
}


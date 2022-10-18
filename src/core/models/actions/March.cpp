#include "March.h"
#include "models/Tick.h"
#include <sstream>
#include <algorithm>
#include "controller/Controller.h"
IAction::Result MarchAction::Do() {
    if ( m_status == IAction::STATUS::WAITING) {
        return DoWaitingInprogress();
    } else if (m_status == IAction::STATUS::INPROGRESS 
            && Singleton<Tick>::instance().GetTicks() >= m_end_tick) {
        return DoInprogressSuccess();
    }
    return {m_status,"", false};
}

IAction::Result MarchAction::DoWaitingInprogress() {
    if ( m_status != IAction::STATUS::WAITING) return {m_status,"", false};
    m_start_tick = (m_is_backward ? m_end_tick : Singleton<Tick>::instance().GetTicks());
    m_status = IAction::STATUS::INPROGRESS;
    auto tick = Singleton<Controller>::instance().TickToPoint(m_id,m_point);
    m_end_tick= m_start_tick+tick;
    Singleton<Controller>::instance().StartMoveObject(m_id);
    m_log << "[" << m_start_tick << "] "
        << "MARCH STARTED " << m_id 
        << " TO " << m_point.x << " " << m_point.y;
    std::string msg = m_log.Log();
    m_log.Clear();
    return {m_status, msg};   
}
IAction::Result MarchAction::DoInprogressSuccess(){
    if (m_status != IAction::STATUS::INPROGRESS 
      || Singleton<Tick>::instance().GetTicks() < m_end_tick) return {m_status, "", false};
    m_status = IAction::STATUS::SUCCESS;
    m_log << "[" << m_end_tick << "] "
           << "MARCH " <<  m_id 
           << " FINISHED " << m_point.x << " " << m_point.y;
    Point prev_pos = Singleton<Controller>::instance().GetObjectPrevPosition(m_id);
    auto ptr = Singleton<Controller>::instance().GetObject(m_point);
    Singleton<Controller>::instance().EndMoveObject(m_id, m_point);
    std::size_t id =0;
    if (ptr.get()) {
        id = ptr->GetId();
    } else {
        id = Singleton<Controller>::instance().FirstCloseObject(m_id);
    }
    if (id) {
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
    std::string msg = m_log.Log();
    m_log.Clear();
    return {m_status, msg};  
}

void MarchAction::SetId(const std::size_t& id) {
    m_id = id;
}
void MarchAction::SetPosition(const Point& p) {
    m_point = p;
}


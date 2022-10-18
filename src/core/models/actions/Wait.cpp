#include "Wait.h"
#include "models/Tick.h"
IAction::Result WaitAction::Do() {
    if (m_status != IAction::STATUS::WAITING)
        return {m_status, "", false};

    m_start_tick = Singleton<Tick>::instance().GetTicks();
    Singleton<Tick>::instance().AddTicks(m_waiting_tick);
    
    m_status = IAction::STATUS::SUCCESS;
    
    m_end_tick = Singleton<Tick>::instance().GetTicks();
    return {m_status,"", false};
}

void WaitAction::SetWaitingTick(const std::size_t& waiting_tick){
    m_waiting_tick = waiting_tick;
}
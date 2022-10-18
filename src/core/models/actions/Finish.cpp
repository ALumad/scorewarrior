#include "Finish.h"
#include "models/Tick.h"
#include <sstream>
#include <iostream>
IAction::Result FinishAction::Do() { 
    if (m_status != IAction::STATUS::WAITING)
        return {m_status, "", false};
    m_start_tick = Singleton<Tick>::instance().GetTicks();
    m_status = IAction::STATUS::SUCCESS;
    m_end_tick = Singleton<Tick>::instance().GetTicks();

    m_log << "[" << m_end_tick << "] " << "FINISH";
    
    return {m_status, m_log.Log()};
}


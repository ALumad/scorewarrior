#pragma once 
#include "IAction.h"
#include "interfaces/IChecker.h"
class WaitAction : public IAction {
public:
    virtual IAction::STATUS Do() override;
    void SetWaitingTick(const std::size_t& waiting_tick);
private:
    std::size_t m_waiting_tick = 0;
};
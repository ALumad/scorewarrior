#pragma once
#include "IAction.h"
#include "utils/Point.h"
#include "utils/Logger.h"
class MarchAction : public IAction {
public:
    MarchAction()=default;
    virtual IAction::STATUS Do() override;
    void SetId(const std::size_t& id);
    void SetPosition(const Point& p);
private:
    IAction::STATUS DoWaitingInprogress();
    IAction::STATUS DoInprogressSuccess();
    std::size_t m_id;
    Point m_point;
    Logger m_log;
};
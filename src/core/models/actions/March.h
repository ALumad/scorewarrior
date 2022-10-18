#pragma once
#include "IAction.h"
#include "utils/Point.h"
#include "utils/Logger.h"
class MarchAction : public IAction {
public:
    MarchAction()=default;
    virtual Result Do() override;
    void SetId(const std::size_t& id);
    void SetPosition(const Point& p);
private:
    IAction::Result DoWaitingInprogress();
    IAction::Result DoInprogressSuccess();
    std::size_t m_id;
    Point m_point;
    Logger m_log;
    bool m_is_backward = false;
};
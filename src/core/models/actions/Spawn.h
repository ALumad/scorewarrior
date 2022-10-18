#pragma once
#include "IAction.h"
#include "utils/Point.h"
#include "utils/Logger.h"
class SpawnAction : public IAction {
public:
    SpawnAction()=default;
    virtual IAction::Result Do() override;
    void SetId(const std::size_t& id);
    void SetPosition(const Point& p);
    void SetStrength(const std::size_t& strength);

private:
    void CreateAndStore();
    std::string Log();
    std::size_t m_id = 0;
    Point m_position;
    std::size_t m_strength = 0;
    Logger m_log;        
};
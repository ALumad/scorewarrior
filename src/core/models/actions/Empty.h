#pragma once 
#include <iostream>
#include "IAction.h"
class EmptyAction : public IAction {
public:
    virtual IAction::Result Do() override {
        if (m_status != STATUS::WAITING) return {m_status, "", false};
        m_status = STATUS::SUCCESS;
        return {m_status, ""};
    }


};
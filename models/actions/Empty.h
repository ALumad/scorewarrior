#pragma once 
#include <iostream>
#include "IAction.h"
class EmptyAction : public IAction {
public:
    virtual STATUS Do() override {
        if (m_status != STATUS::WAITING) return m_status;
        std::cout << std::endl;
        m_status = STATUS::SUCCESS;
        return m_status;
    }


};
#pragma once 
#include <iostream>
#include "IAction.h"
#include "utils/Logger.h"
class TerminateAction : public IAction {
public:
    TerminateAction(const std::string& msg) {
        what(msg);
    }
    virtual STATUS Do() override {
        std::cout << m_logger.Log() << std::endl;
        std::exit(0);
        return m_status;
    }

    void what(const std::string& msg) {
        m_logger << msg;
    }

private:
    Logger m_logger;

};
#pragma once
#include "IAction.h"
#include "utils/Logger.h"
class FinishAction : public IAction {
public:
    virtual Result Do() override ;
public:
    Logger m_log;    
};
#pragma once
#include <vector>
#include <memory>
#include "models/actions/IAction.h"
class ActionsReader {
public:
    ActionsReader(char* path);
    void Read(char* path);
    std::vector<std::shared_ptr<IAction>> PopActions();
    
private:
    std::string Prepare(const std::string& str);
    std::vector<std::shared_ptr<IAction>> m_queue;
};
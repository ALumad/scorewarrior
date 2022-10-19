#pragma once
#include <vector>
#include <queue>
#include <memory>
#include "models/actions/IAction.h"

class  ActionsRunner {
public:
    void Execute(std::vector<std::shared_ptr<IAction>>& actions);


private:
    void DoQueueAction(std::queue<std::shared_ptr<IAction>>& queue);

};
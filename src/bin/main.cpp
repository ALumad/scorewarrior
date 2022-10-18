#include <iostream>
#include "utils/ActionsReader.h"
#include "models/Map.h"
#include <queue>
#include "models/actions/Wait.h"
#include "models/actions/Finish.h"

void DoQueueAction(std::queue<std::shared_ptr<IAction>>& queue){
    while(!queue.empty()) 
    {
        IAction::Result res = {IAction::STATUS::WAITING, ""};
        do {
            res = queue.front()->Do();
            if (res.is_printable)
                std::cout << res.message << std::endl;
        } while (res.status != IAction::STATUS::SUCCESS && res.status != IAction::STATUS::SUCCESS);
        queue.pop();
    }
}


int main(int argc, char **argv){
    if (argc < 2) return 0;
    ActionsReader cr(argv[1]);
    auto q_actions = cr.PopActions();
    std::queue<std::shared_ptr<IAction>> q_inprogress;
    for (auto a: q_actions){
        if (dynamic_cast<FinishAction*>(a.get())) { 
            DoQueueAction(q_inprogress); 
        }
        auto res = a->Do();
        if (res.is_printable)
            std::cout << res.message << std::endl;
        if (res.status == IAction::STATUS::INPROGRESS)
            q_inprogress.push(a);
        if (dynamic_cast<WaitAction*>(a.get())) {
            DoQueueAction(q_inprogress);
        }   
        
    }
    
    return 0;
}
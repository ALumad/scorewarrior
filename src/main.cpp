#include <iostream>
#include "utils/ActionsReader.h"
#include "models/Map.h"
#include <queue>
#include "models/actions/Wait.h"
#include "models/actions/Finish.h"

void DoQueueAction(std::queue<std::shared_ptr<IAction>>& queue){
    while(!queue.empty()) 
    {
        auto res = IAction::STATUS::WAITING;
        do {
            res = queue.front()->Do();
        } while (res != IAction::STATUS::SUCCESS && res != IAction::STATUS::SUCCESS);
        queue.pop();
    }
}


int main(int argc, char **argv){
    if (argc < 2) return 0;
    ActionsReader cr(argv[1]);
    auto q_actions = cr.PopActions();
    std::queue<std::shared_ptr<IAction>> q_inprogress;
    for (auto& a: q_actions){
        if (dynamic_cast<FinishAction*>(a.get())) { 
            DoQueueAction(q_inprogress); 
        }
        a->Do();
        if (a->GetStatus() == IAction::STATUS::INPROGRESS)
            q_inprogress.push(a);
            
        if (dynamic_cast<WaitAction*>(a.get())) {
            DoQueueAction(q_inprogress);
        }   
        
    }
    
    return 0;
}
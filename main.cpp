#include <iostream>
#include "utils/ActionsReader.h"
#include "models/Map.h"
#include <queue>
#include "models/actions/Wait.h"
int main(int argc, char **argv){
    if (argc < 2) return 0;
    ActionsReader cr(argv[1]);
    auto q_actions = cr.PopActions();
    std::queue<std::shared_ptr<IAction>> q_inprogress;
    for (auto& a: q_actions){
        a->Do();
        if (a->GetStatus() == IAction::STATUS::INPROGRESS)
            q_inprogress.push(a);
        if (dynamic_cast<WaitAction*>(a.get())){
            while(!q_inprogress.empty()){
                q_inprogress.front()->Do();
                q_inprogress.pop();
            }
        }
    }
    return 0;
}
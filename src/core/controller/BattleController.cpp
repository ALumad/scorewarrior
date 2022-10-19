#include "BattleController.h"
#include "models/objects/Atacker.h"
#include "models/objects/Range.h"
#include "Controller.h"
#include <iostream>
int BattleController::Battle(const std::size_t& id1, const std::size_t& id2){
    Controller& controller = Singleton<Controller>::instance();
    auto ptr1 = controller.GetObject(id1).get();
    auto ptr2 = controller.GetObject(id2).get();
    int res = 0;
    if (dynamic_cast<Range*>(ptr1) || dynamic_cast<Range*>(ptr1)) {
        res = DistanceBattle(id1, id2);
    } else {
        res =  dynamic_cast<Atacker*>(ptr1)->Atack() - dynamic_cast<Atacker*>(ptr2)->Atack();
    }
    if (res < 0) {
        return res;
    } else if (res > 0) {
        controller.DropObject(id2);
    }
    else {
        controller.DropObject(id1);
        controller.DropObject(id2);
    }
    return res;
}


int BattleController::DistanceBattle(const std::size_t& id1, const std::size_t& id2) {
    Controller& controller = Singleton<Controller>::instance();
    auto warrior1 = dynamic_cast<Atacker*>(controller.GetObject(id1).get());
    auto warrior2 = dynamic_cast<Atacker*>(controller.GetObject(id2).get());

    auto range1 = dynamic_cast<Range*>(warrior1);
    auto range2 = dynamic_cast<Range*>(warrior2);    
    int res = 0;

    if (range1 && range2){
        if (range1->GetDistance() == range2->GetDistance())
            return range1->Atack() - range2->Atack();
        else if (range1->GetDistance() < range2->GetDistance()) {
            return -1;
        }
        else {
            if (range1->Atack() >= range2->Atack()) return 1;
            return -1;
        }
    }
    else if (range1) {
        if (range1->Atack() >= warrior2->Atack()) return 1;
        return -1;        
    } else {
        if (range2->Atack() >= warrior1->Atack()) return -1;
        return 1;        
    }
    return 0; //Will never happend
}   


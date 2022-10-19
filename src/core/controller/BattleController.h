#pragma once

#include "utils/Singleton.h"


class BattleController :public Singleton<BattleController>{
public:
    int Battle(const std::size_t& id1, const std::size_t& id2);
private:    
    int DistanceBattle(const std::size_t& id1, const std::size_t& id2);

};
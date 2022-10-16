#include "ActionFactory.h"
#include "ActionBuilder.h"
#include "models/actions/Terminate.h"
#include <string>
#include <sstream>
#include <iostream>
std::shared_ptr<IAction> ActionsFactory::ActionFromLine(const std::string& line){
    using namespace ActionsStringName;
    std::stringstream ss(line);
    std::string tmp;
    std::vector<std::string> elems;
    //std::cout << line << "\n";
    while (std::getline(ss, tmp, ' ')) {
        elems.push_back(tmp);
    }
    if (elems[0] == CREATE_MAP) return CreateMapAction(elems);
    if (elems[0] == SPAWN) return SpawnAction(elems);
    if (elems[0] == MARCH) return MarchAction(elems);
    if (elems[0] == WAIT) return WaitAction(elems);
    if (elems[0] == FINISH) return FinishAction(elems);
    if (elems[0] == EMPTY) return EmptyAction(elems);
    std::stringstream sserr;
    sserr << "Unknow command "  << elems[0] << " in line " << line << std::endl;
    return std::make_shared<TerminateAction>(sserr.str());
};

std::shared_ptr<IAction> 
    ActionsFactory::CreateMapAction(const std::vector<std::string>& elems) 
{
    if (elems.size() != 3) throw 1;
    std::size_t weight = std::stoi(elems[1]);
    std::size_t height = std::stoi(elems[2]);
    CreateMapActionBuilder builder;
    builder.CreateAction().SetMapSize(weight, height);
    return builder.Build();
}

std::shared_ptr<IAction> 
    ActionsFactory::SpawnAction(const std::vector<std::string>& elems) 
{
    if (elems.size() != 5) throw 1;
    std::size_t id = std::stoi(elems[1]);
    std::size_t x = std::stoi(elems[2]);
    std::size_t y = std::stoi(elems[3]);
    std::size_t strength = std::stoi(elems[4]);
    SpawnActionBuilder builder;
    builder.CreateAction()
        .SetSpawnId(id)
        .SetSpawnPosition({x,y})
        .SetSpawnStrength(strength);
    return builder.Build();
}
std::shared_ptr<IAction> 
    ActionsFactory::MarchAction(const std::vector<std::string>& elems) 
{
    if (elems.size() != 4) throw 1;
    std::size_t id = std::stoi(elems[1]);
    std::size_t x = std::stoi(elems[2]);
    std::size_t y = std::stoi(elems[3]);
    MarchActionBuilder builder;
    builder.CreateAction()
        .SetMarchId(id)
        .SetMarchPosition({x,y});
    return builder.Build();
}

std::shared_ptr<IAction> 
    ActionsFactory::WaitAction(const std::vector<std::string>& elems) 
{
    if (elems.size() != 2) throw 1;
    std::size_t tick = std::stoi(elems[1]);
    WaitActionBuilder builder;
    builder.CreateAction().SetWaitTick(tick);
    return builder.Build();
}

std::shared_ptr<IAction> 
    ActionsFactory::FinishAction(const std::vector<std::string>& elems) 
{
    if (elems.size() != 1) throw 1;
    FinishActionBuilder builder;
    builder.CreateAction();
    return builder.Build();
}

std::shared_ptr<IAction> ActionsFactory::EmptyAction(const std::vector<std::string>& elems){
    BaseActionBuilder builder;
    builder.CreateAction(elems[0]);
    return builder.Build();   
}
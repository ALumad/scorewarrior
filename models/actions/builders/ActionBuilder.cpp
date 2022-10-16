#include <map>
#include <functional>
#include "ActionBuilder.h"
#include "models/actions/CreateMap.h"
#include "models/actions/Spawn.h"
#include "models/actions/Wait.h"
#include "models/actions/Finish.h"
#include "models/actions/March.h"
#include "models/actions/Empty.h"

using namespace ActionsStringName;

BaseActionBuilder& BaseActionBuilder::CreateAction(const std::string& action) {
    
    static std::map<std::string, std::function<IAction*()>> factory {
        {CREATE_MAP, [](){return new CreateMapAction();}},
        {SPAWN, [](){return new SpawnAction();}},
        {MARCH, []() {return new MarchAction();}},
        {WAIT, [](){return new WaitAction();}},
        {FINISH, [](){return new FinishAction();}},
        {EMPTY, [](){return new EmptyAction();}}
    };
    m_action = std::shared_ptr<IAction>(factory[action]());
    return *this;
}
std::shared_ptr<IAction> BaseActionBuilder::Build() { return std::move(m_action); }

FinishActionBuilder& FinishActionBuilder::CreateAction() {
    BaseActionBuilder::CreateAction(FINISH);
    return *this;   
}


WaitActionBuilder& WaitActionBuilder::CreateAction(){
    BaseActionBuilder::CreateAction(WAIT);
    return *this;
}

WaitActionBuilder& WaitActionBuilder::SetWaitTick(const std::size_t& tickCount) {
    dynamic_cast<WaitAction*>(m_action.get())->SetWaitingTick(tickCount);
    return *this;   
};


CreateMapActionBuilder& CreateMapActionBuilder::CreateAction(){
    BaseActionBuilder::CreateAction(CREATE_MAP);
    return *this;   
}


CreateMapActionBuilder& CreateMapActionBuilder::SetMapSize(const std::size_t&  width, const std::size_t&  height) {
    auto* ptr = dynamic_cast<CreateMapAction*>(m_action.get());
    if (ptr){
        ptr->SetMapSize(width, height);
    };
    return *this;
}

SpawnActionBuilder& SpawnActionBuilder::CreateAction(){
    BaseActionBuilder::CreateAction(SPAWN);
    return *this;       
}

SpawnActionBuilder& SpawnActionBuilder::SetSpawnId(const std::size_t& id) {
    dynamic_cast<SpawnAction*>(m_action.get())->SetId(id);
    return *this;
}

SpawnActionBuilder& SpawnActionBuilder::SetSpawnPosition(const Point& p) {
    dynamic_cast<SpawnAction*>(m_action.get())->SetPosition(p);
    return *this;
}

SpawnActionBuilder& SpawnActionBuilder::SetSpawnStrength(const std::size_t& strength){
    dynamic_cast<SpawnAction*>(m_action.get())->SetStrength(strength);    
    return *this;
}


MarchActionBuilder& MarchActionBuilder::CreateAction(){
    BaseActionBuilder::CreateAction(MARCH);
    return *this;       
}

MarchActionBuilder& MarchActionBuilder::SetMarchId(const std::size_t& id) {
    dynamic_cast<MarchAction*>(m_action.get())->SetId(id);
    return *this;
}

MarchActionBuilder& MarchActionBuilder::SetMarchPosition(const Point& p) {
    dynamic_cast<MarchAction*>(m_action.get())->SetPosition(p);
    return *this;
}


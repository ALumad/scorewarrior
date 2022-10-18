#pragma once
#include <memory>
#include "models/actions/IAction.h"
#include "models/Map.h"


class BaseActionBuilder {
public:
    BaseActionBuilder& CreateAction(const std::string& action);
    std::shared_ptr<IAction> Build();
    virtual ~BaseActionBuilder() = default; 
protected:
    std::shared_ptr<IAction> m_action;
    
};

class FinishActionBuilder  : public BaseActionBuilder {
public:
    FinishActionBuilder& CreateAction();
};


class WaitActionBuilder  : public BaseActionBuilder {
public:
    WaitActionBuilder& CreateAction();
    WaitActionBuilder& SetWaitTick(const std::size_t& tickCount);
};

class CreateMapActionBuilder : public BaseActionBuilder {
public:
    CreateMapActionBuilder& CreateAction();
    CreateMapActionBuilder& SetMapSize(const std::size_t&  width, const std::size_t&  height);
};


class SpawnActionBuilder : public BaseActionBuilder {
public:
    SpawnActionBuilder& CreateAction();
    SpawnActionBuilder& SetSpawnId(const std::size_t& id);
    SpawnActionBuilder& SetSpawnPosition(const Point& p);
    SpawnActionBuilder& SetSpawnStrength(const std::size_t& strength);    
};


class MarchActionBuilder : public BaseActionBuilder {
public:
    MarchActionBuilder& CreateAction();
    MarchActionBuilder& SetMarchId(const std::size_t& id);
    MarchActionBuilder& SetMarchPosition(const Point& p);
};

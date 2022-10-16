#pragma once
#include "ActionBuilder.h"
class ActionsFactory {
public:
    static std::shared_ptr<IAction> ActionFromLine(const std::string& line);
private:
    static std::shared_ptr<IAction> CreateMapAction(const std::vector<std::string>& elems);
    static std::shared_ptr<IAction> SpawnAction(const std::vector<std::string>& elems);
    static std::shared_ptr<IAction> MarchAction(const std::vector<std::string>& elems);
    static std::shared_ptr<IAction> WaitAction(const std::vector<std::string>& elems);
    static std::shared_ptr<IAction> FinishAction(const std::vector<std::string>& elems);
    static std::shared_ptr<IAction> EmptyAction(const std::vector<std::string>& elems);
};
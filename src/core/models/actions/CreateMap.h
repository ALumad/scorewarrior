#pragma once
#include <cstdlib>
#include "IAction.h"
#include "interfaces/IChecker.h"
#include "utils/Logger.h"
class CreateMapAction : public IAction, public IChecker {
    public:
        CreateMapAction()=default;
        CreateMapAction(const std::size_t& width, const std::size_t& height);
        virtual Result Do() override;
        virtual bool Check() override;

        void SetMapSize(const std::size_t& width, const std::size_t& height);
        
       
    private:
        std::string Log();
        Logger m_log;
        std::size_t m_width = 0;
        std::size_t m_height = 0;

};
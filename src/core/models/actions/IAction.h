#pragma once
#include <string>
namespace ActionsStringName {
    const std::string CREATE_MAP = "CREATE_MAP";
    const std::string SPAWN = "SPAWN";
    const std::string SPAWN_RANGE = "SPAWN_RANGE";
    const std::string MARCH = "MARCH";
    const std::string WAIT = "WAIT";
    const std::string FINISH = "FINISH";
    const std::string EMPTY = "EMPTY";
};
class IAction {
public:
    enum class STATUS {
        WAITING,
        INPROGRESS,
        SUCCESS,
        FAILURE,

    };

    struct Result {
        STATUS status;
        std::string message;
        bool is_printable = true;
    };

    virtual Result Do() = 0;
    virtual STATUS GetStatus()  {return m_status;}
    virtual ~IAction() = default;
protected:
    std::size_t m_start_tick;
    std::size_t m_end_tick;  
    STATUS m_status = STATUS::WAITING;
};


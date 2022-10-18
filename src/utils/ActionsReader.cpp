#include "ActionsReader.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include "models/actions/builders/ActionFactory.h"
#include "InputChecker.h"
namespace fs = std::filesystem;

ActionsReader::ActionsReader(char* path){
    Read(path);
}
std::vector<std::shared_ptr<IAction>> ActionsReader::PopActions(){
    return m_queue;
}

std::string ActionsReader::Prepare(const std::string& str){
    const std::string excluded = " \n\r\t\f\v";
    std::string res = str;
    size_t start = str.find_first_not_of(excluded);
    if  (start != std::string::npos)
        res = res.substr(start);
    else return "EMPTY";

    size_t end = str.find_last_not_of(excluded);
    if (end != std::string::npos) 
       res = res.substr(0, end + 1);
    else return "EMPTY";

    return res;
}

void ActionsReader::Read(char* path){
    std::ifstream ifs = std::ifstream (path, std::ios::in);
    std::string str;
    
    if(ifs.is_open())  {
        while ( !ifs.eof() )
        {
            std::getline ( ifs, str);
            str = Prepare(str);
            if (!InputChecker::IsLineCorrect(str)) continue;
            auto action = ActionsFactory::ActionFromLine(str);
            m_queue.push_back(action);
        }
        ifs.close();
    }
}
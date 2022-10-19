#include "utils/ActionsReader.h"
#include "utils/ActionsRunner.h"



int main(int argc, char **argv){
    if (argc < 2) return 0;
    ActionsReader cr(argv[1]);
    auto q_actions = cr.PopActions();
    ActionsRunner runner;
    runner.Execute(q_actions);
    
    return 0;
}
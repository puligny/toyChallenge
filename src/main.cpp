#include <iostream>

#include "toyrobot.h"
#include "instructionhandler.h"

int main(int argc, char ** argv)
{
    std::shared_ptr<ToyRobot> robot(new ToyRobot);

    if (argc > 1) {
        InstructionHandler handler(robot,argv[1]);
        handler.run();
    } else {
        InstructionHandler handler(robot);
        handler.run();
    }

    return 0;
}

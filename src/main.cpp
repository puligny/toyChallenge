#include <iostream>

#include "toyrobot.h"
#include "instructionhandler.h"

int main(int argc, char ** argv)
{
    std::shared_ptr<ToyRobot> robot(new ToyRobot);
    InstructionHandler handler(robot);

    handler.run();

    return 0;
}

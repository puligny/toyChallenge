#include "instructionhandlertests.h"
#include "instructionhandler.h"

int testStringToDirection() {
    std::shared_ptr<ToyRobot> robot;
    InstructionHandler handler(robot);

    if (handler.stringToDirection("NORTH") != NORTH)
        return -1;

    if (handler.stringToDirection("EAST") != EAST)
        return -1;

    if (handler.stringToDirection("SOUTH") != SOUTH)
        return -1;

    if (handler.stringToDirection("WEST") != WEST)
        return -1;

    if (handler.stringToDirection("NONE") != NONE)
        return -1;

    if (handler.stringToDirection("MAX") != NONE)
        return -1;

    if (handler.stringToDirection("FOO") != NONE)
        return -1;

    if (handler.stringToDirection("") != NONE)
        return -1;

    return 0;
}

int testExecuteInstruction() {
    std::shared_ptr<ToyRobot> robot(new ToyRobot);
    InstructionHandler handler(robot);

    // test that commands called before placed fails
    if (handler.executeInstruction("MOVE"))
        return -1;

    if (handler.executeInstruction("LEFT"))
        return -1;

    if (handler.executeInstruction("RIGHT"))
        return -1;

    if (handler.executeInstruction("REPORT"))
        return -1;

    if (handler.executeInstruction("PLACE 0,1,SOUTH") == false)
        return -1;

    if (handler.executeInstruction("MOVE") == false)
        return -1;

    if (handler.executeInstruction("LEFT") == false)
        return -1;

    if (handler.executeInstruction("RIGHT") == false)
        return -1;

    if (handler.executeInstruction("REPORT") == false)
        return -1;

    if (handler.executeInstruction("FOO"))
        return -1;

    if (handler.executeInstruction("PLACE BAD_ARGS"))
        return -1;

    return 0;
}

int testRunFile() {
    std::shared_ptr<ToyRobot> robot(new ToyRobot);
    InstructionHandler invalid(robot,"../tests/invalid.txt");
    if (invalid.run())
        return -1;

    InstructionHandler allCmds(robot,"../tests/allcmds.txt");
    if (allCmds.run() == false)
        return -1;

    return 0;
}

int instructionHandlerTests()
{
    int res = 0;

    res += testStringToDirection();
    res += testExecuteInstruction();
    res += testRunFile();

    return res;
}

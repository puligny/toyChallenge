#include "instructionhandlertests.h"
#include "instructionhandler.h"

#include <iostream>
#include <sstream>
#include <string.h>

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

    // test that commands called before placed fail silently
    if (handler.executeInstruction("MOVE") == false)
        return -1;

    if (handler.executeInstruction("LEFT") == false)
        return -1;

    if (handler.executeInstruction("RIGHT") == false)
        return -1;

    if (handler.executeInstruction("REPORT") == false)
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

    InstructionHandler complex(robot,"../tests/complex.txt");
    if (complex.run() == false)
        return -1;

    return 0;
}

int testInteractiveMode() {
    std::stringstream input;
    std::streambuf* prevcinbuf = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(output.rdbuf());
    std::shared_ptr<ToyRobot> robot(new ToyRobot);
    InstructionHandler handler(robot);

    // add some input instructions
    input << "PLACE 2,3,EAST" << std::endl
          << "MOVE" << std::endl
          << "RIGHT" << std::endl
          << "REPORT" << std::endl
          << "q" << std::endl;
    handler.run();

    // test that commands have been handled and last REPORT cmd correctly outputted
    std::string report = output.str();
    report = report.substr(report.find("table.\n")+strlen("table.\n"), strlen("3,3,SOUTH\n"));
    if (report.compare("3,3,SOUTH\n")) {
        std::cin.rdbuf(prevcinbuf);
        std::cout.rdbuf(prevcoutbuf);
        return -1;
    }


    std::cin.rdbuf(prevcinbuf);
    std::cout.rdbuf(prevcoutbuf);

    return 0;
}

int instructionHandlerTests()
{
    int res = 0;

    res += testStringToDirection();
    res += testExecuteInstruction();
    res += testRunFile();
    res += testInteractiveMode();

    return res;
}

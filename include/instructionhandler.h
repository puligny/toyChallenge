#ifndef INSTRUCTIONHANDLER_H
#define INSTRUCTIONHANDLER_H

#include <memory>
#include <fstream>

#include "toyrobot.h"

class InstructionHandler
{
public:
    InstructionHandler(std::shared_ptr<ToyRobot> robot, std::string fileName="");
    virtual ~InstructionHandler();

    bool run();
    bool executeInstruction(std::string instruction);
    enum direction stringToDirection(std::string word);

private:
    std::shared_ptr<ToyRobot> mRobot;
    std::ifstream             mFile;
};

#endif // INSTRUCTIONHANDLER_H

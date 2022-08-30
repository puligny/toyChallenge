#ifndef INSTRUCTIONHANDLER_H
#define INSTRUCTIONHANDLER_H

#include <memory>
#include <fstream>

#include "toyrobot.h"

/**
 * @brief This handler can parse and execute instructions for a ToyRobot.
 *
 * It can be constructed with or without an instruction file.
 * To start this handler, call the run() method. If an instruction file was given,
 * it will execute all instructions present in the file. Otherwise, it will start
 * the interactive interface and read instructions from the input.
 * It is also possible to execute a single instruction thanks to the
 * executeInstruction() method.
 */
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

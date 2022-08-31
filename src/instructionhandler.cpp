#include "instructionhandler.h"

#include <iostream>
#include <regex>

using namespace std;

/**
 * @brief InstructionHandler constructor.
 * @param robot pointer to the ToyRobot.
 * @param fileName [optional] path to an instruction file.
 */
InstructionHandler::InstructionHandler(shared_ptr<ToyRobot> robot, string fileName)
    : mRobot(robot)
{
    if (fileName.empty() == false) {
        mFile.open(fileName);
        if (mFile.bad()) {
            cerr << "Invalid file name " << fileName << endl;
        }
    }
}

/**
 * @brief InstructionHandler destructor.
 */
InstructionHandler::~InstructionHandler()
{
    if (mFile.is_open())
        mFile.close();
}

/**
 * @brief InstructionHandler::run main method of the Instruction handler.
 * If an input file was given during construction of the object,
 * execute all instructions present in the file one by one.
 * Otherwise, start the interactive interface and await input instruction.
 * @return true if all instructions have been executed successfully.
 */
bool InstructionHandler::run()
{
    if (mFile.is_open() && mFile.good()) {
        string instruction;
        while(getline(mFile,instruction)) {
            if (executeInstruction(instruction) == false)
                return false;
        }
        return true;
    } else {
        string input;
        cout << "Welcome to the toy robot challenge !!!" << endl << endl
             << "You can interact with the toy using the following commands:" << endl
             << "PLACE X,Y,F" << endl
             << "MOVE" << endl
             << "LEFT" << endl
             << "RIGHT" << endl
             << "REPORT" << endl << endl
             << "If you want to stop playing, simply input 'q'" << endl
             << "Please start by placing the robot anywhere on the 5x5 table." << endl;
        do {
            getline(cin, input);
            if (input == "q") {
                cout << endl << "Thanks for playing !" << endl
                     << "See you soon." << endl;
                break;
            }

            if (executeInstruction(input) == false)
                return false;

        } while(input != "q");

        return true;
    }
}

/**
 * @brief InstructionHandler::executeInstruction parse and execute a single instruction.
 * @param instruction the instruction string.
 * @return true if the instruction was executed successfully.
 */
bool InstructionHandler::executeInstruction(string instruction)
{
    string key = instruction.substr(0, instruction.find(' '));
    if (key == "PLACE") {
        string args = instruction.substr(instruction.find(' ')+1); // +1 to skip the whitespace
        if (regex_match(args,regex("[0-9],[0-9],\\w+")) == false) {
            cerr << "invalids arguments for command PLACE" << endl;
            return false;
        }
        int x,y;
        char comma;
        string sDir;
        stringstream(args) >> x >> comma >> y >> comma >> sDir;
        enum direction dir = stringToDirection(sDir);
        if (dir == NONE) {
            cerr << sDir << " is not a known direction" << endl;
            return false;
        }
        mRobot->place(x, y, dir);

    } else if (key == "MOVE") {
        if (mRobot->isPlaced() == false) {
            cerr << "cannot execute instruction " << key << ". Robot is not placed." << endl;
            return true;
        }
        mRobot->move();

    } else if (key == "LEFT") {
        if (mRobot->isPlaced() == false) {
            cerr << "cannot execute instruction " << key << ". Robot is not placed." << endl;
            return true;
        }
        mRobot->rotate(false);

    } else if (key == "RIGHT") {
        if (mRobot->isPlaced() == false) {
            cerr << "cannot execute instruction " << key << ". Robot is not placed." << endl;
            return true;
        }
        mRobot->rotate(true);

    } else if (key == "REPORT") {
        if (mRobot->isPlaced() == false) {
            cerr << "cannot execute instruction " << key << ". Robot is not placed." << endl;
            return true;
        }
        mRobot->report();

    } else {
        cerr << "invalid command " << key << endl;
        return false;
    }

    return true;
}

/**
 * @brief InstructionHandler::stringToDirection converts a string to a direction value.
 * If the string is invalid, it will return direction NONE.
 * @param word The input direction as a string
 * @return The output direction value. [SOUTH,EAST,NORTH,WEST,NONE]
 */
direction InstructionHandler::stringToDirection(std::string word)
{
    if (word == "SOUTH")
        return SOUTH;
    else if (word == "EAST")
        return EAST;
    else if (word == "NORTH")
        return NORTH;
    else if (word == "WEST")
        return WEST;
    else
        return NONE;
}

#include "instructionhandler.h"

#include <iostream>
#include <regex>

using namespace std;

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

InstructionHandler::~InstructionHandler()
{
    if (mFile.is_open())
        mFile.close();
}

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

bool InstructionHandler::executeInstruction(string instruction)
{
    string key = instruction.substr(0, instruction.find(' '));
    if (key == "PLACE") {
        string args = instruction.substr(instruction.find(' ')+1); // +1 to skip the whitespace
        if (regex_match(args,regex("[0-4],[0-4],\\w"))) {
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
            return false;
        }
        mRobot->move();

    } else if (key == "LEFT") {
        if (mRobot->isPlaced() == false) {
            cerr << "cannot execute instruction " << key << ". Robot is not placed." << endl;
            return false;
        }
        mRobot->rotate(false);

    } else if (key == "RIGHT") {
        if (mRobot->isPlaced() == false) {
            cerr << "cannot execute instruction " << key << ". Robot is not placed." << endl;
            return false;
        }
        mRobot->rotate(true);

    } else if (key == "REPORT") {
        if (mRobot->isPlaced() == false) {
            cerr << "cannot execute instruction " << key << ". Robot is not placed." << endl;
            return false;
        }
        mRobot->report();

    } else {
        cerr << "invalid command " << key << endl;
        return false;
    }

    return true;
}

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

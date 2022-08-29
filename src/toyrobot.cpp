#include "toyrobot.h"

#include <iostream>
#include <sstream>

using namespace std;

std::ostream& operator<<(std::ostream& os, direction c)
{
    switch(c)
    {
        case NONE  : os << "NONE";  break;
        case NORTH   : os << "NORTH";   break;
        case EAST : os << "EAST"; break;
        case SOUTH   : os << "SOUTH";   break;
        case WEST  : os << "WEST";  break;
        default    : os.setstate(std::ios_base::failbit);
    }
    return os;
}

ToyRobot::ToyRobot(unsigned int width, unsigned int height)
    : mWidth(width)
    , mHeight(height)
    , mX(-1)
    , mY(-1)
    , mDirection(NONE)
{
}

bool ToyRobot::move()
{
    if (!mPlaced)
        return false;

    switch (mDirection) {

    case NONE:
        return false;
    case NORTH:
        if (mY >= 4)
            return false;
        else
            mY++;
        break;
    case EAST:
        if (mX >= 4)
            return false;
        else
            mX++;
        break;
    case SOUTH:
        if (mY <= 0)
            return false;
        else
            mY--;
        break;
    case WEST:
        if (mX <= 0)
            return false;
        else
            mX--;
        break;
    default:
        return false;
    }

    return true;
}

bool ToyRobot::place(unsigned int x, unsigned int y, enum direction dir)
{
    if (x >= mWidth || y >= mHeight) {
        cerr << "cannot place robot, coordinates are out of range." << endl;
        return false;
    }

    mX = x;
    mY = y;
    mDirection = dir;
    mPlaced = true;
    return true;
}

void ToyRobot::rotate(bool right)
{
    if (!mPlaced)
        return;

    if (right)
        mDirection = (enum direction)(((int)mDirection + 1) % 4);
    else
        mDirection = (enum direction)(((int)mDirection - 1) % 4);
}

void ToyRobot::report()
{
    if (!mPlaced)
        return;

    cout << mX << ',' << mY << ',' << mDirection << endl;
}

int ToyRobot::x() const
{
    return mX;
}

int ToyRobot::y() const
{
    return mY;
}

direction ToyRobot::direction() const
{
    return mDirection;
}

string ToyRobot::getDirection() const
{
    stringstream s;
    s << mDirection;
    return s.str();
}

bool ToyRobot::isPlaced() const
{
    return mPlaced;
}

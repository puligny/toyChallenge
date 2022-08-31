#include "toyrobot.h"

#include <iostream>
#include <sstream>

using namespace std;

/**
 * @brief overload operator << for the direction in order to print a direction.
 * @param os output stream.
 * @param c input direction.
 * @return output stream.
 */
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

/**
 * @brief ToyRobot constructor.
 * @param width of the table.
 * @param height of the table.
 */
ToyRobot::ToyRobot(unsigned int width, unsigned int height)
    : mWidth(width)
    , mHeight(height)
    , mX(-1)
    , mY(-1)
    , mDirection(NONE)
{
}

/**
 * @brief ToyRobot::move Move the robot one unit forward.
 * Will be executed only if the robot is placed and moving won't cause the robot to fall.
 */
void ToyRobot::move()
{
    if (!mPlaced) {
        cerr << "cannot move robot before it is placed." << endl;
        return;
    }

    switch (mDirection) {

    case NONE:
        return;
    case NORTH:
        if (mY < (mHeight - 1))
            mY++;
        break;
    case EAST:
        if (mX < (mWidth - 1))
            mX++;
        break;
    case SOUTH:
        if (mY > 0)
            mY--;
        break;
    case WEST:
        if (mX > 0)
            mX--;
        break;
    default:
        break;
    }
}

/**
 * @brief ToyRobot::place Place the robot at the given position and direction.
 * @param x input X position [0-4]
 * @param y input Y position [0-4]
 * @param dir input direction [NORTH,EAST,SOUTH,WEST]
 * @return true if the robot has been successfully placed.
 */
bool ToyRobot::place(unsigned int x, unsigned int y, enum direction dir)
{
    if (x >= mWidth || y >= mHeight) {
        cerr << "cannot place robot, coordinates are out of range." << endl;
        return false;
    }
    if (dir >= MAX || dir <= NONE) {
        cerr << "cannot place robot, direction is invalid." << endl;
        return false;
    }

    mX = x;
    mY = y;
    mDirection = dir;
    mPlaced = true;
    return true;
}

/**
 * @brief ToyRobot::rotate Turn the robot left or right without changing its position.
 * @param right Boolean to indicate if the robot must turn to the right or to the left.
 */
void ToyRobot::rotate(bool right)
{
    if (!mPlaced) {
        cerr << "cannot rotate robot before it is placed." << endl;
        return;
    }

    if (right)
        mDirection = (enum direction)(((int)mDirection + 1) % MAX);
    else {
        int newDir = mDirection - 1;
        if (newDir < 0)
            newDir = MAX - 1;
        mDirection = (enum direction) newDir;
    }
}

/**
 * @brief ToyRobot::report output the position and direction of the robot in the console.
 */
void ToyRobot::report()
{
    if (!mPlaced) {
        cerr << "cannot report position before the robot is placed." << endl;
        return;
    }

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

/**
 * @brief ToyRobot::getDirection return the direction as a string.
 * @return output direction as a string.
 */
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

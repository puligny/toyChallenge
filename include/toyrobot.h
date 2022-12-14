#ifndef TOYROBOT_H
#define TOYROBOT_H

#include <string>

enum direction {
    NONE = -1,
    NORTH,
    EAST,
    SOUTH,
    WEST,
    MAX
};

/**
 * @brief This is a toy robot that can move on a 5x5 table.
 * The robot must be placed before executing any other instruction.
 */
class ToyRobot
{
public:
    ToyRobot(unsigned int width=5, unsigned int  height=5);

    void move();
    bool place(unsigned int x, unsigned int y, direction dir);
    void rotate(bool right);
    void report();

    int x() const;
    int y() const;
    enum direction direction() const;
    std::string getDirection() const;
    bool isPlaced() const;

private:
    unsigned int mWidth;
    unsigned int mHeight;
    bool         mPlaced = false;

    int            mX;
    int            mY;
    enum direction mDirection;
};

#endif // TOYROBOT_H

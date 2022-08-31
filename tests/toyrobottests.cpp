#include "toyrobottests.h"
#include "toyrobot.h"

#include <iostream>
#include <sstream>

int testConstructor() {
    // test default constructor initialization
    ToyRobot robot;
    if (robot.isPlaced() || robot.direction() != NONE
            || robot.x() != -1 || robot.x() != -1)
        return -1;

    // test a robot with a smaller table
    ToyRobot small(2, 2);
    if (small.isPlaced() || small.direction() != NONE
            || small.x() != -1 || small.x() != -1)
        return -1;

    if (small.place(0, 0, NORTH) == false)
        return -1;
    small.move();
    small.move();
    if (small.y() != 1)
        return -1;
    small.rotate(true);
    small.move();
    small.move();
    if (small.x() != 1)
        return -1;

    return 0;
}

int testPlace() {
    ToyRobot robot;
    if (robot.isPlaced())
        return -1;
    // test a negative position
    if (robot.place(-1, 0, EAST))
        return -1;
    // robot shall not be considered placed if given a bad position
    if (robot.isPlaced())
        return -1;
    // test out of range position
    if (robot.place(0, 18, WEST))
        return -1;
    // test an invalid direction
    if (robot.place(2, 3, NONE))
        return -1;
    // test an invalid direction
    if (robot.place(2, 3, MAX))
        return -1;
    // test a valid position
    if (robot.place(0, 0, NORTH) == false)
        return -1;
    if (robot.isPlaced() == false)
        return -1;
    // test if it is possible to place again a robot already placed
    if (robot.place(2, 3, SOUTH) == false)
        return -1;
    return 0;
}

int testMove() {
    ToyRobot robot;
    // cannot move until the robot is placed
    robot.move();
    if (robot.x() != -1 || robot.y() != -1)
        return -1;

    robot.place(0, 0, NORTH);
    robot.move();
    // move shall only place the robot one step further
    // north direction increments y position
    if (robot.x() != 0 || robot.y() != 1)
        return -1;

    // robot refuses to fall from the table
    robot.move();
    robot.move();
    robot.move();
    robot.move();
    if (robot.y() != 4)
        return -1;

    // test to move to a negative position by facing west
    robot.rotate(false);
    robot.move();
    if (robot.x() != 0)
        return -1;

    // test south direction
    robot.rotate(false);
    robot.move();
    robot.move();
    robot.move();
    robot.move();
    robot.move();
    if (robot.y() != 0)
        return -1;

    // test east direction
    robot.rotate(false);
    robot.move();
    robot.move();
    robot.move();
    robot.move();
    robot.move();
    if (robot.x() != 4)
        return -1;

    return 0;
}

int testRotate() {
    ToyRobot robot;
    // cannot rotate before robot is placed
    robot.rotate(true);
    if (robot.direction() != NONE)
        return -1;
    robot.rotate(false);
    if (robot.direction() != NONE)
        return -1;

    robot.place(0,0,NORTH);
    if (robot.direction() != NORTH)
        return -1;
    // test rotate right
    robot.rotate(true);
    if (robot.direction() != EAST)
        return -1;
    // test rotate left
    robot.rotate(false);
    if (robot.direction() != NORTH)
        return -1;

    // test a whole turn on the right
    robot.rotate(true);
    if (robot.direction() != EAST)
        return -1;
    robot.rotate(true);
    if (robot.direction() != SOUTH)
        return -1;
    robot.rotate(true);
    if (robot.direction() != WEST)
        return -1;
    robot.rotate(true);
    if (robot.direction() != NORTH)
        return -1;

    // test a whole turn on the left
    robot.rotate(false);
    if (robot.direction() != WEST)
        return -1;
    robot.rotate(false);
    if (robot.direction() != SOUTH)
        return -1;
    robot.rotate(false);
    if (robot.direction() != EAST)
        return -1;
    robot.rotate(false);
    if (robot.direction() != NORTH)
        return -1;

    return 0;
}

int testReport() {
    ToyRobot robot;
    std::stringstream output;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(output.rdbuf());

    // test that report does not output anything before robot is placed.
    robot.report();
    if (output.str().empty() == false) {
        std::cout.rdbuf(prevcoutbuf);
        return -1;
    }

    // test that report output the correct position and direction
    robot.place(4, 2, SOUTH);
    robot.report();
    if (output.str().compare("4,2,SOUTH\n")) {
        std::cout.rdbuf(prevcoutbuf);
        return -1;
    }

    std::cout.rdbuf(prevcoutbuf);

    return 0;
}

int toyRobotTests()
{
    int res = 0;

    res += testConstructor();
    res += testPlace();
    res += testMove();
    res += testRotate();
    res += testReport();

    return res;
}

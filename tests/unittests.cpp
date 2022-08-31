#include "toyrobottests.h"
#include "instructionhandlertests.h"

int main(int argc, char ** argv)
{
    int res = 0;
    res += toyRobotTests();
    res += instructionHandlerTests();

    return res;
}

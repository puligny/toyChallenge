# toyChallenge

The toyChallenge is a simple program that can control a toy robot on a 5x5 table.

## Build

The project can be compiled using CMake.
If you do not have CMake installed, you can download it on Windows at https://cmake.org/download/ or run `sudo apt install cmake` on Linux.

To compile, first create a build directory and run the cmake command :
```
mkdir build && cd build
cmake ..
```
Then you can compile targets with make command :
```
make
```

This will build two binaries :
- **toyChallenge** : Toy challenge program that can be run from the console.
- **unitTests** : unit tests of the different classes of the toy challenge.

## Run challenge

The toy challenge can be used in two forms :

### Interactive interface

If the binary is called with no arguments, it will start the interactive interface.
The user can inputs commands one by one in the console and output will also be displayed in this console.
Possible commands are :
- PLACE X,Y,F : place the robot at the position X,Y and facing F direction (NORTH,EAST,SOUTH,WEST).
- MOVE : move the robot one unit forward in the direction it is facing. It will not move if it has reached the end of the table.
- LEFT : rotate the robot 90° to the left.
- RIGHT : rotate the robot 90° to the right.
- REPORT : output the position of the robot in the console with following format: X,Y,F.
- q : exit the interactive interface gracefully.

### File interface

The binary can also be called with a file as argument. In this case, the program will execute one by one each command present in the file.
Each command must be on a separate line and output will be in the console where the binary is called.
Example files are available in the *example* folder.

## Tests

To run tests, simply run command ` make test `

## Design

The toy challenge is composed of two classes :
- **ToyRobot** : the toy robot that can be placed, moved, rotated or report its position.
- **InstructionHandler** : handler that can parse and call commands on a robot. The run method can either start the interactive interface or execute the instruction in the input file.


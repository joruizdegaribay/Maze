#ifndef MAZE_H

#define MAZE_H

#include "Arduino.h"
#include "Position.h"

#define MAZE_WIDTH   9

class Maze {

  public:
    void begin(byte mazeStructure[MAZE_WIDTH][MAZE_WIDTH], byte mazeMap[MAZE_WIDTH][MAZE_WIDTH]);

    bool isGoalPosition(Position position);
    Position nextPathPosition(Position position);
    
  private:
    byte _mazeStructure[MAZE_WIDTH][MAZE_WIDTH];
    byte _mazeOutMap[MAZE_WIDTH][MAZE_WIDTH];
    
    void _printMaze(byte maze[MAZE_WIDTH][MAZE_WIDTH]);
};

#endif

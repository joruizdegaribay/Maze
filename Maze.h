#ifndef MAZE_H

#define MAZE_H

#include "Arduino.h"
#include "Position.h"
#include "Location.h"
#include "ListLib.h"

#define MAZE_WIDTH   9

class Maze {

  public:
    void begin(byte mazeStructure[MAZE_WIDTH][MAZE_WIDTH], byte mazeMap[MAZE_WIDTH][MAZE_WIDTH]);

    int8_t startSearch(uint8_t cellValue);
    int8_t addNewCell(Location newLocation, uint8_t cellValue);
    bool isLocated();
    Location getLocation();

    bool isGoalPosition(Position position);
    Position nextPathPosition(Position position);
    
  private:
    byte _mazeStructure[MAZE_WIDTH][MAZE_WIDTH];
    byte _mazeOutMap[MAZE_WIDTH][MAZE_WIDTH];
    
    byte _mazeEastStructure[MAZE_WIDTH][MAZE_WIDTH];
    byte _mazeSouthStructure[MAZE_WIDTH][MAZE_WIDTH];
    byte _mazeWestStructure[MAZE_WIDTH][MAZE_WIDTH];
    
    List<Location> _startLocations;
    Location _realLocation;
    
    Location _calculeLocation(Location displacement);
    byte _rotateRight4bits(byte value, byte bits);
    byte _rotateLeft4bits(byte value, byte bits);    
    void _printMaze(byte maze[MAZE_WIDTH][MAZE_WIDTH]);
};

#endif

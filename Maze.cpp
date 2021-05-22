#include "Maze.h"

/*
Begin maze object
*/
void Maze::begin(byte mazeStructure[MAZE_WIDTH][MAZE_WIDTH], byte mazeMap[MAZE_WIDTH][MAZE_WIDTH]) {

  // copy maze estructure into out map
  for (byte i = 0; i < MAZE_WIDTH; i++) {
    for (byte j = 0; j < MAZE_WIDTH; j++) {
      _mazeStructure[i][j] = mazeStructure[i][j];
      _mazeOutMap[i][j] = mazeMap[i][j];
    }
  }
}

/*
Get if the position is the goal
*/
bool Maze::isGoalPosition(Position position) {

  //If the cell value is 0, this position is the goal
  if (_mazeOutMap[position.x][position.y] == 0){
    return true;
  }
  else {
    return false;
  }
}

/*
Get the next position of the out path in this maze
*/
Position Maze::nextPathPosition(Position position) {

  //check if is the goal position
  if (isGoalPosition(position)){
    return Position(-1, -1);
  }

  byte nextCellValue = _mazeOutMap[position.x][position.y] - 1;

  //checks if the top cell is the following
  if ((position.x > 0) && (_mazeOutMap[position.x - 1][position.y] == nextCellValue)) {
    //it is verified that there is no wall
    if ((_mazeStructure[position.x][position.y] & 0b0001) == 0b0000) {
	return Position(position.x - 1, position.y);
    }
  }

  //checks if the right cell is the following
  if ((position.y < 8) && (_mazeOutMap[position.x][position.y + 1] == nextCellValue)) {
    //it is verified that there is no wall
    if ((_mazeStructure[position.x][position.y] & 0b0010) == 0b0000) {
      return Position(position.x, position.y + 1);
    }
  }

  //checks if the bottom cell is the following
  if ((position.x < 8) && (_mazeOutMap[position.x + 1][position.y] == nextCellValue)) {
    //it is verified that there is no wall
    if ((_mazeStructure[position.x][position.y] & 0b0100) == 0b0000) {
      return Position(position.x + 1, position.y);
    }
  }

  //checks if the left cell is the following
  if ((position.y > 0) && (_mazeOutMap[position.x][position.y - 1] == nextCellValue)) {
    //it is verified that there is no wall
    if ((_mazeStructure[position.x][position.y] & 0b1000) == 0b0000) {
      return Position(position.x, position.y -1);
    }
  }

  //error
  return Position(-1, -1);
}

/*
Print in serial terminal maze codification
*/
void Maze::_printMaze(byte maze[MAZE_WIDTH][MAZE_WIDTH]) {
  for (byte i = 0; i < MAZE_WIDTH; i++) {
    for (byte j = 0; j < MAZE_WIDTH; j++) {
      Serial.print(maze[i][j]);
      Serial.print("\t");
    }
    Serial.println("");
  }
}

#include "Maze.h"

//#define DEBUG_MAZE_STRUCTURE
//#define DEBUG_MAZE_SEARCH

/*
Begin maze object
*/
void Maze::begin(byte mazeStructure[MAZE_WIDTH][MAZE_WIDTH], byte mazeMap[MAZE_WIDTH][MAZE_WIDTH]) {

  //copy maze estructure with NORTH orientation and the out map
  for (byte i = 0; i < MAZE_WIDTH; i++) {
    for (byte j = 0; j < MAZE_WIDTH; j++) {
      this->_mazeStructure[i][j] = mazeStructure[i][j];
      this->_mazeOutMap[i][j] = mazeMap[i][j];
    }
  }
  //initialize east orientation estructure
  for (byte i = 0; i < MAZE_WIDTH; i++) {
    for (byte j = 0; j < MAZE_WIDTH; j++) {
      this->_mazeEastStructure[MAZE_WIDTH - 1 - j][i] = this->_rotateRight4bits(this->_mazeStructure[i][j], 1);
    }
  }
#ifdef DEBUG_MAZE_STRUCTURE
  Serial.println();
  Serial.println("Maze east orientation structure:");
  this->_printMaze(_mazeEastStructure);
#endif
  // initialize south orientation structure
  for (byte i = 0; i < MAZE_WIDTH; i++) {
    for (byte j = 0; j < MAZE_WIDTH; j++) {
      this->_mazeSouthStructure[MAZE_WIDTH - 1 - i][MAZE_WIDTH - 1 - j] = this->_rotateRight4bits(this->_mazeStructure[i][j], 2);
    }
  }
#ifdef DEBUG_MAZE_STRUCTURE
  Serial.println();
  Serial.println("Maze south orientation structure:");
  this->_printMaze(this->_mazeSouthStructure);
#endif
  // initialize west orientation structure
  for (byte i = 0; i < MAZE_WIDTH; i++) {
    for (byte j = 0; j < MAZE_WIDTH; j++) {
      this->_mazeWestStructure[j][MAZE_WIDTH - 1 - i] = this->_rotateRight4bits(this->_mazeStructure[i][j], 3);
    }
  }
#ifdef DEBUG_MAZE_STRUCTURE
  Serial.println();
  Serial.println("Maze west orientation structure:");
  this->_printMaze(this->_mazeWestStructure);
#endif
}

/*

*/
int8_t Maze::startSearch(uint8_t cellValue){

  this->_startLocations.Clear();

  // se recorre la estructura del laberinto con orientación norte
  for (byte x = 0; x < MAZE_WIDTH; x++) {
    for (byte y = 0; y < MAZE_WIDTH; y++) {
      if (this->_mazeStructure[x][y] == cellValue) {
        Location tempLocation(x, y, NORTH);
        this->_startLocations.Add(tempLocation);
      }
    }
  }
  // se recorre la estructura del laberinto con orientación este
  for (byte x = 0; x < MAZE_WIDTH; x++) {
    for (byte y = 0; y < MAZE_WIDTH; y++) {
      if (this->_mazeEastStructure[x][y] == cellValue) {
        Location tempLocation(x, y, EAST);
        this->_startLocations.Add(tempLocation);
      }
    }
  }
  // se recorre la estructura del laberinto con orientación sur
  for (byte x = 0; x < MAZE_WIDTH; x++) {
    for (byte y = 0; y < MAZE_WIDTH; y++) {
      if (this->_mazeSouthStructure[x][y] == cellValue) {
        Location tempLocation(x, y, SOUTH);
        this->_startLocations.Add(tempLocation);
      }
    }
  }
  // se recorre la estructura del laberinto con orientación oeste
  for (byte x = 0; x < MAZE_WIDTH; x++) {
    for (byte y = 0; y < MAZE_WIDTH; y++) {
      if (this->_mazeWestStructure[x][y] == cellValue) {
        Location tempLocation(x, y, WEST);
        this->_startLocations.Add(tempLocation);
      }
    }
  }
#ifdef DEBUG_MAZE_SEARCH
  Serial.println();
  Serial.println("Start locations list values (0-north, 1-east, 2-south, 3-west):");
  for (int i = 0; i < this->_startLocations.Count(); i++) {
    Serial.print((String)"    [" + i + "] - ");
    this->_startLocations[i].println(&Serial);
  }
#endif

  if (this->_startLocations.Count() == 1){
    this->_realLocation = this->_startLocations[0];
#ifdef DEBUG_MAZE_SEARCH
    Serial.println();
    Serial.println("Real location found  (0-north, 1-east, 2-south, 3-west):");
    this->_realLocation.println(&Serial);
#endif
  }

  return this->_startLocations.Count();
}

/*

*/
int8_t Maze::addNewCell(Location newLocation, uint8_t cellValue){

  //se corrije el valor de la celda en función de la orientación
  switch(newLocation.orientation){
    case EAST:
      cellValue = this->_rotateLeft4bits(cellValue, 1);
      break;
    case SOUTH:
      cellValue = this->_rotateLeft4bits(cellValue, 2);
      break;
    case WEST:
      cellValue = this->_rotateLeft4bits(cellValue, 3);
      break;
  }

  // se compruebas todas las posiciones de partida
  for (int i = this->_startLocations.Count() - 1; i >= 0; i--) {
    Position tempPosition(this->_startLocations[i].x + newLocation.x, this->_startLocations[i].y + newLocation.y);
    if ((tempPosition.x < 0) || (tempPosition.x >= MAZE_WIDTH)) {
      this->_startLocations.Remove(i);
    }
    else if ((tempPosition.y < 0) && (tempPosition.y >= MAZE_WIDTH)) {
      this->_startLocations.Remove(i);
    }
    else {
      switch (this->_startLocations[i].orientation) {
        case NORTH:
          if (this->_mazeStructure[tempPosition.x][tempPosition.y] != cellValue) {
            this->_startLocations.Remove(i);
          }
          break;
        case EAST:
          if (this->_mazeEastStructure[tempPosition.x][tempPosition.y] != cellValue) {
            this->_startLocations.Remove(i);
          }
          break;
        case SOUTH:
          if (this->_mazeSouthStructure[tempPosition.x][tempPosition.y] != cellValue) {
            this->_startLocations.Remove(i);
          }
          break;
        case WEST:
          if (this->_mazeWestStructure[tempPosition.x][tempPosition.y] != cellValue) {
            this->_startLocations.Remove(i);
          }
          break;
      }
    }
  }
#ifdef DEBUG_MAZE_SEARCH
  Serial.println();
  Serial.println("Start location list values (0-north, 1-east, 2-south, 3-west):");
  for (int i = 0; i < this->_startLocations.Count(); i++) {
    Serial.print((String)"    [" + i + "] - ");
    this->_startLocations[i].println(&Serial);
  }
#endif
  if (this->_startLocations.Count() == 1){
    _realLocation = this->_calculeLocation(newLocation);
#ifdef DEBUG_MAZE_SEARCH
    Serial.println();
    Serial.println("Real location found  (0-north, 1-east, 2-south, 3-west):");
    this->_realLocation.println(&Serial);
#endif
  }
  return this->_startLocations.Count();
}

/*

*/
bool Maze::isLocated(){

  if (this->_startLocations.Count() == 1)
    return true;
  else
    return false;
}

/*

*/
Location Maze::getLocation(){

  if (this->_startLocations.Count() == 1){
    return _realLocation;
  }
  else{
    return Location(-1, -1, NORTH);
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
  if ((position.y < (MAZE_WIDTH - 1)) && (_mazeOutMap[position.x][position.y + 1] == nextCellValue)) {
    //it is verified that there is no wall
    if ((_mazeStructure[position.x][position.y] & 0b0010) == 0b0000) {
      return Position(position.x, position.y + 1);
    }
  }

  //checks if the bottom cell is the following
  if ((position.x < (MAZE_WIDTH - 1)) && (_mazeOutMap[position.x + 1][position.y] == nextCellValue)) {
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

Location Maze::_calculeLocation(Location displacement){

    Location tempLocation;
    //calcule position into the maze with start location and displacement
    switch (this->_startLocations[0].orientation) {
      case NORTH:
        tempLocation.x = this->_startLocations[0].x + displacement.x;
        tempLocation.y = this->_startLocations[0].y + displacement.y;
        break;
      case EAST:
        tempLocation.x = this->_startLocations[0].y + displacement.y;
        tempLocation.y = MAZE_WIDTH - 1 - this->_startLocations[0].x - displacement.x;
        break;
      case SOUTH:
        tempLocation.x = MAZE_WIDTH - 1 - this->_startLocations[0].x - displacement.x;
        tempLocation.y = MAZE_WIDTH - 1 - this->_startLocations[0].y - displacement.y;
        break;
      case WEST:
        tempLocation.x = MAZE_WIDTH - 1 - this->_startLocations[0].y - displacement.y;
        tempLocation.y = this->_startLocations[0].x + displacement.x;
        break;
    }
    //calcule and adjust the orientation
    tempLocation.orientation = this->_startLocations[0].orientation + displacement.orientation;
    if (tempLocation.orientation < 0) {
      tempLocation.orientation += 4;
    }
    else if (tempLocation.orientation >= 4) {
      tempLocation.orientation -= 4;
    }
    return tempLocation;
}

/*

*/
byte Maze::_rotateRight4bits(byte value, byte bits) {

  byte newValue = value;
  for (int i = 0; i < bits; i++) {
    if ((newValue & 0x01) == 0)
      newValue >>= 1;
    else {
      newValue >>= 1;
      newValue |= 0x08;
    }
  }
  return newValue;
}

/*

*/
byte Maze::_rotateLeft4bits(byte value, byte bits) {

  byte newValue = value;
  for (int i = 0; i < bits; i++) {
    newValue <<= 1;
    if ((newValue & 0x10) != 0) {
      newValue &= 0x0F;
      newValue |= 0x01;
    }
  }
  return newValue;
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

#include "Maze.h"
#include "Position.h"

Maze maze;

//Start position for the robot
Position robotPosition(4, 7);

// Maze structure codification
byte mazeStructure[MAZE_WIDTH][MAZE_WIDTH] = {
  {13, 5, 5, 1, 5, 7, 13, 5, 3},
  {13, 1, 5, 0, 5, 5, 3, 9, 6},
  {13, 6, 9, 4, 5, 5, 2, 8, 7},
  {11, 9, 4, 7, 9, 7, 10, 8, 3},
  {10, 8, 5, 3, 12, 3, 8, 6, 14},
  {10, 8, 5, 2, 9, 4, 4, 5, 3},
  {12, 2, 13, 4, 4, 5, 1, 5, 6},
  {13, 6, 9, 3, 13, 5, 4, 1, 7},
  {13, 5, 6, 12, 5, 5, 5, 4, 7}
};
// Maze out map
byte mazeOutMap[MAZE_WIDTH][MAZE_WIDTH] = {
  {28, 27, 26, 25, 26, 27, 26, 25, 24},
  {27, 26, 25, 24, 23, 22, 21, 22, 23},
  {28, 27, 22, 23, 22, 21, 20, 21, 22},
  {23, 20, 21, 22, 19, 20, 19, 20, 21},
  {22, 19, 18, 17, 18, 17, 18, 19, 22},
  {21, 18, 17, 16, 15, 16, 17, 16, 15},
  {20, 19, 16, 15, 14, 13, 12, 13, 14},
  {21, 20, 3, 4, 13, 12, 11, 10, 11},
  {0, 1, 2, 5, 6, 7, 8, 9, 10}
};

void setup() {

  Serial.begin(9600);

  maze.begin(mazeStructure, mazeOutMap);

  Serial.println("Press any key to start robot search");
  Serial.println();
}

void loop() {

  //when receive any caracter from Serial port
  if (Serial.available()) {
    Serial.read();
    int counter = 0;
    //go through the maze to the goal
    while (!maze.isGoalPosition(robotPosition)) {
      Serial.print((String)"[Step " + counter + "] Robot position: ");
      robotPosition.print(&Serial);
      robotPosition = maze.nextPathPosition(robotPosition);
      Serial.print("\tNext: ");
      robotPosition.println(&Serial);
      Serial.println();
      counter++;
    }
  }
}

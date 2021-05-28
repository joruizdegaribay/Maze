#ifndef LOCATION_H

#define LOCATION_H

#include "Position.h"

#define NORTH	0
#define EAST	1
#define SOUTH	2
#define WEST	3

class Location : public Position {

  public:
    uint8_t orientation;
    
    Location() {
      this->x = 0;
      this->y = 0;
      this->orientation = NORTH;
    }
    Location(int8_t x, int8_t y, uint8_t orientation) {
      this->x = x;
      this->y = y;
      this->orientation = orientation;
    }
    void update(int8_t x, int8_t y, uint8_t orientation) {
      this->x = x;
      this->y = y;
      this->orientation = orientation;
    }
    void print(Stream *port) {
      port->print((String)"X: " + (int)this->x + "\tY: " + (int)this->y + "\t->: "+ this->orientation);
    }
    void println(Stream *port) {
      port->println((String)"X: " + (int)this->x + "\tY: " + (int)this->y + "\t->: "+ this->orientation);
    }
};

#endif

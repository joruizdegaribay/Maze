#ifndef POSITION_H

#define POSITION_H

class Position {

  public:
    int8_t x;
    int8_t y;

    Position() {
      this->x = 0;
      this->y = 0;
    }
    Position(int8_t x, int8_t y) {
      this->x = x;
      this->y = y;
    }
    void update(int8_t x, int8_t y) {
      this->x = x;
      this->y = y;
    }
    void print(Stream *port) {
      port->print((String)"X: " + this->x + "\tY: " + this->y);
    }
    void println(Stream *port) {
      port->println((String)"X: " + this->x + "\tY: " + this->y);
    }
};

#endif

#ifndef POSITION_H

#define POSITION_H

class Position {

  public:
    char x;
    char y;

    Position() {
      this->x = 0;
      this->y = 0;
    }
    Position(char x, char y) {
      this->x = x;
      this->y = y;
    }
    void update(char x, char y) {
      this->x = x;
      this->y = y;
    }
    void print(Stream *port) {
      port->print((String)"X: " + (int)this->x + "\tY: " + (int)this->y);
    }
    void println(Stream *port) {
      port->println((String)"X: " + (int)this->x + "\tY: " + (int)this->y);
    }
};

#endif

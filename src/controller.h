#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running,std::vector<Snake> &snakes ) const;
  //void HandleInputP1(bool &running, Snake &snake) const;
  //void HandleInputP2(bool &running, Snake &snake) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif
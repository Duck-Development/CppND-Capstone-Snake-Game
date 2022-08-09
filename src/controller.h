#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <memory>

class Controller {
 public:
  void HandleInput(bool &running,std::vector<std::shared_ptr<Snake>> &snakes ) const;


 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif
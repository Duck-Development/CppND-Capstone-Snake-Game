#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include <deque>
#include <mutex>

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height ,int _head_x , int _head_y)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(_head_x),
        head_y(_head_y) {

        }

  void Update();
  void GrowBody();
  SDL_Point GetHead()  ;
  std::deque<SDL_Point>  GetBody();
  bool SnakeCell(int x, int y);
  
  void IncreaseSpeed(double _speed);
  bool const  IsAlive();
  int const GetSize();
  void SetDir(Direction dir);
  Direction GetDir() ;
  void Colide();
  
 private:
  void UpdateHead();
  void UpdateBody(const SDL_Point &&current_cell, SDL_Point &&prev_cell);
  float speed{0.1f};
  bool alive{true};
  bool growing{false};
  const int grid_width;
  const int grid_height;
  int size{1};
  float head_x;
  float head_y;
  std::mutex _mtx;
  Direction direction = Direction::kUp;
  std::deque<SDL_Point> body;
  
  
};

#endif
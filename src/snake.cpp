#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update()
{
  SDL_Point prev_cell(GetHead()); // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell(GetHead()); // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  {
    std::lock_guard<std::mutex> lock(_mtx);
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
    {
      UpdateBody(std::move(current_cell), std::move(prev_cell));
    }
  }
}

void Snake::UpdateHead()
{
  std::lock_guard<std::mutex> lock(_mtx);
  switch (direction)
  {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(const SDL_Point &&current_head_cell, SDL_Point &&prev_head_cell)
{
  // Add previous head location to vector
  body.emplace_back(std::move(prev_head_cell));

  if (!growing)
  {
    // Remove the tail from the vector.
    body.pop_front();
  }
  else
  {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body)
  {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y)
    {
      alive = false;
    }
  }
}

SDL_Point Snake::GetHead()
{
  std::lock_guard<std::mutex> lock(_mtx);
  return SDL_Point{static_cast<int>(head_x), static_cast<int>(head_y)};
}

void Snake::GrowBody() { 
  std::lock_guard<std::mutex> lock(_mtx);
  growing = true; 
  }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y)
{
  std::lock_guard<std::mutex> lock(_mtx);
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y))
  {
    return true;
  }
  for (auto const &item : body)
  {
    if (x == item.x && y == item.y)
    {
      return true;
    }
  }
  return false;
}

std::deque<SDL_Point> Snake::GetBody()
{
  std::lock_guard<std::mutex> lock(_mtx);
  return body;
}

void Snake::IncreaseSpeed(double _speed)
{
  std::lock_guard<std::mutex> lock(_mtx);
  speed += _speed;
};
bool const Snake::IsAlive()
{
  std::lock_guard<std::mutex> lock(_mtx);
  return alive;
};
int const Snake::GetSize()
{
  std::lock_guard<std::mutex> lock(_mtx);
  return size;
}
void Snake::SetDir(Direction dir)
{
  std::lock_guard<std::mutex> lock(_mtx);
  direction = dir;
}
Snake::Direction Snake::GetDir()
{
  std::lock_guard<std::mutex> lock(_mtx);
  return direction;
}
void Snake::Colide()
{
  std::lock_guard<std::mutex> lock(_mtx);
  alive = false;
}
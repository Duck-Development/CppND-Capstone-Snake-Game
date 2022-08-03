#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const
{
  if (snake.GetDir() != opposite || snake.GetSize() == 1)
    snake.SetDir(input);
  return;
}

void Controller::HandleInput(bool &running, std::vector<Snake> &snakes) const
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      running = false;
    }
  }

  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_UP])
  {
    ChangeDirection(snakes[0], Snake::Direction::kUp,
                    Snake::Direction::kDown);
  }
  else if (state[SDL_SCANCODE_DOWN])
  {
    ChangeDirection(snakes[0], Snake::Direction::kDown,
                    Snake::Direction::kUp);
  }
  else if (state[SDL_SCANCODE_LEFT])
  {
    ChangeDirection(snakes[0], Snake::Direction::kLeft,
                    Snake::Direction::kRight);
  }
  else if (state[SDL_SCANCODE_RIGHT])
  {
    ChangeDirection(snakes[0], Snake::Direction::kRight,
                    Snake::Direction::kLeft);
  }

  if (state[SDL_SCANCODE_W])
  {
    ChangeDirection(snakes[1], Snake::Direction::kUp,
                    Snake::Direction::kDown);
  }
  else if (state[SDL_SCANCODE_S])
  {
    ChangeDirection(snakes[1], Snake::Direction::kDown,
                    Snake::Direction::kUp);
  }
  else if (state[SDL_SCANCODE_A])
  {
    ChangeDirection(snakes[1], Snake::Direction::kLeft,
                    Snake::Direction::kRight);
  }
  else if (state[SDL_SCANCODE_D])
  {
    ChangeDirection(snakes[1], Snake::Direction::kRight,
                    Snake::Direction::kLeft);
  }
}
#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height):
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {

  snakes.emplace_back( std::make_shared<Snake>(grid_width, grid_height,  random_w(engine) , random_h(engine)));
  snakes.emplace_back( std::make_shared<Snake>(grid_width, grid_height,  random_w(engine) , random_h(engine)));
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snakes);
    Update();

    renderer.Render(snakes, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snakes[0]->SnakeCell(x, y) && !snakes[1]->SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snakes[0]->IsAlive() || !snakes[1]->IsAlive() ) return;

  snakes[0]->Update();
  snakes[1]->Update();

  auto&& newHead0 = snakes[0]->GetHead();

  // Check if there's food over here
  if (food.x == newHead0.x && food.y == newHead0.y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snakes[0]->GrowBody();
    snakes[0]->IncreaseSpeed(0.02);
  }
  
  auto&& newHead1 = snakes[1]->GetHead();

  // Check if there's food over here
  if (food.x == newHead1.x && food.y == newHead1.y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snakes[1]->GrowBody();
    snakes[1]->IncreaseSpeed(0.02);
  }

// Snake Colision
if (newHead0.x == newHead1.x && newHead0.y == newHead1.y)
{
  snakes[0]->Colide();
  snakes[1]->Colide();
  return;
}

if (snakes[0]->SnakeCell(newHead1.x ,newHead1.y))
{
  snakes[1]->Colide();
  return;
}

if (snakes[1]->SnakeCell(newHead0.x ,newHead0.y))
{
  snakes[0]->Colide();
  return;
}

}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snakes[0]->GetSize()+snakes[1]->GetSize(); }
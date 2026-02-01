#include <filesystem>
#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "SDL.h"
#include "statslogger.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  const std::filesystem::path log_path{"stats.txt"};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  StatsLogger stats_logger(log_path, SDL_GetTicks());
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame, stats_logger);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}

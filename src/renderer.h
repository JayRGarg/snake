#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "sdl_wrappers.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
 void UpdateWindowTitle(int score, int fps);

 private:
  SdlVideo sdl_video;
  SdlWindow sdl_window;
  SdlRenderer sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif

#ifndef SDL_WRAPPERS_H
#define SDL_WRAPPERS_H

#include <iostream>
#include "SDL.h"

class SdlVideo {
 public:
  explicit SdlVideo(Uint32 flags) {
    if (SDL_Init(flags) < 0) {
      std::cerr << "SDL could not initialize.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
  }

  ~SdlVideo() { SDL_Quit(); }

  SdlVideo(const SdlVideo &) = delete;
  SdlVideo &operator=(const SdlVideo &) = delete;
  SdlVideo(SdlVideo &&) = delete;
  SdlVideo &operator=(SdlVideo &&) = delete;
};

class SdlWindow {
 public:
  SdlWindow() = default;
  SdlWindow(const char *title, int x, int y, int w, int h, Uint32 flags)
      : handle_(SDL_CreateWindow(title, x, y, w, h, flags)) {}

  ~SdlWindow() { Reset(); }

  SdlWindow(const SdlWindow &) = delete;
  SdlWindow &operator=(const SdlWindow &) = delete;

  SdlWindow(SdlWindow &&other) noexcept : handle_(other.handle_) {
    other.handle_ = nullptr;
  }

  SdlWindow &operator=(SdlWindow &&other) noexcept {
    if (this != &other) {
      Reset();
      handle_ = other.handle_;
      other.handle_ = nullptr;
    }
    return *this;
  }

  SDL_Window *get() const { return handle_; }

 private:
  void Reset() {
    if (handle_ != nullptr) {
      SDL_DestroyWindow(handle_);
      handle_ = nullptr;
    }
  }

  SDL_Window *handle_{nullptr};
};

class SdlRenderer {
 public:
  SdlRenderer() = default;
  SdlRenderer(SDL_Window *window, int index, Uint32 flags)
      : handle_(SDL_CreateRenderer(window, index, flags)) {}

  ~SdlRenderer() { Reset(); }

  SdlRenderer(const SdlRenderer &) = delete;
  SdlRenderer &operator=(const SdlRenderer &) = delete;

  SdlRenderer(SdlRenderer &&other) noexcept : handle_(other.handle_) {
    other.handle_ = nullptr;
  }

  SdlRenderer &operator=(SdlRenderer &&other) noexcept {
    if (this != &other) {
      Reset();
      handle_ = other.handle_;
      other.handle_ = nullptr;
    }
    return *this;
  }

  SDL_Renderer *get() const { return handle_; }

 private:
  void Reset() {
    if (handle_ != nullptr) {
      SDL_DestroyRenderer(handle_);
      handle_ = nullptr;
    }
  }

  SDL_Renderer *handle_{nullptr};
};

#endif

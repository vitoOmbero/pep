#include <string>
#include <iostream>

#include "engine/engine.h"
#include "utils/terminal.h"

#include "SDL.h"

/*
 * windows?
 *
 *
#if __has_include(<SDL.h>)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

 *
 */


void AtExit() { pep::AtExitMessage(); }

std::ostream& operator<<(std::ostream& out, const SDL_version& v)
{
  out << static_cast<int>(v.major) << '.';
  out << static_cast<int>(v.minor) << '.';
  out << static_cast<int>(v.patch);
  return out;
}

#pragma pack(push, 4)
struct bind
{
    SDL_Keycode      key;
    std::string_view name;
};
#pragma pack(pop)

void check_input(const SDL_Event& e)
{
  using namespace std;

  const array<::bind, 8> keys{ { { SDLK_w, "up" },
                                       { SDLK_a, "left" },
                                       { SDLK_s, "down" },
                                       { SDLK_d, "right" },
                                       { SDLK_LCTRL, "button_one" },
                                       { SDLK_SPACE, "button_two" },
                                       { SDLK_ESCAPE, "select" },
                                       { SDLK_RETURN, "start" } } };

  const auto it = find_if(begin(keys), end(keys), [&](const ::bind& b) {
      return b.key == e.key.keysym.sym;
  });

  if (it != end(keys))
  {
    cout << it->name << ' ';
    if (e.type == SDL_KEYDOWN)
    {
      cout << "is pressed" << endl;
    }
    else
    {
      cout << "is released" << endl;
    }
  }
}

int main() {
  int result = std::atexit(AtExit);

  if (result != 0) {
    Terminal::ReportErr("AtExit registration failed\n");
    return EXIT_FAILURE;
  }

  SDL_version compiled = { 0, 0, 0 };
  SDL_version linked   = { 0, 0, 0 };

  SDL_VERSION(&compiled)
  SDL_GetVersion(&linked);

  std::cout << "compiled: " << compiled << '\n';
  std::cout << "linked: " << linked << std::endl;

  bool is_good = std::cout.good();

  if (!is_good){
    return EXIT_FAILURE;
  }

  if (SDL_COMPILEDVERSION !=
      SDL_VERSIONNUM(linked.major, linked.minor, linked.patch))
  {
    std::cerr << "warning: SDL2 compiled and linked version mismatch: "
         << compiled << " " << linked << std::endl;
  }

  const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
  if (init_result != 0)
  {
    const char* err_message = SDL_GetError();
    std::cerr << "error: failed call SDL_Init: " << err_message << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Window* const window = SDL_CreateWindow("title",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              640,
                                              480,
                                              ::SDL_WINDOW_OPENGL);

  if (window == nullptr)
  {
    const char* err_message = SDL_GetError();
    std::cerr << "error: failed call SDL_CreateWindow: " << err_message << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }

  bool continue_loop = true;
  while (continue_loop)
  {
    SDL_Event sdl_event;

    while (SDL_PollEvent(&sdl_event))
    {
      switch (sdl_event.type)
      {
        case SDL_KEYDOWN:
          check_input(sdl_event);
          break;
        case SDL_KEYUP:
          check_input(sdl_event);
          break;
        case SDL_QUIT:
          continue_loop = false;
          break;
        default:
          break;
      }
    }
  }

  std::cout << "2 secs to exit..." << std::endl;

  SDL_Delay( 2000 );

  SDL_DestroyWindow(window);

  SDL_Quit();

  std::exit(EXIT_SUCCESS);
}

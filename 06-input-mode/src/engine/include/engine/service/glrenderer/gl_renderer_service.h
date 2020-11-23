#ifndef INC_05_GUESS_NUMBER_GL_RENDERER_SERVICE_H
#define INC_05_GUESS_NUMBER_GL_RENDERER_SERVICE_H

#include "gl_renderer.h"
#include "SDL.h"

namespace GlRendererService{
    void SetActiveWindow(SDL_Window* window);
    void Render(GlRenderer& gl_renderer);
}

#endif //INC_05_GUESS_NUMBER_GL_RENDERER_SERVICE_H

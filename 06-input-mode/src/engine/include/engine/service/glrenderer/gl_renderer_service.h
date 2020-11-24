#ifndef INC_05_GUESS_NUMBER_GL_RENDERER_SERVICE_H
#define INC_05_GUESS_NUMBER_GL_RENDERER_SERVICE_H

#include "gl_renderer.h"
#include "SDL.h"

namespace GlRendererService{
    void SetActiveWindow(SDL_Window* window);
    void Render();

    void InitFor(size_t level_id);

    void Destroy();
}

#endif //INC_05_GUESS_NUMBER_GL_RENDERER_SERVICE_H

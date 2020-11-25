#ifndef INC_05_GUESS_NUMBER_GL_RENDERER_SERVICE_H
#define INC_05_GUESS_NUMBER_GL_RENDERER_SERVICE_H

#include "gl_renderer.h"
#include "SDL.h"
#include "gl_types.h"
#include "gl_color.h"

namespace GlRendererService{
    void SetActiveWindow(SDL_Window* window);

    void Render();

    void InitFor(size_t level_id);

    void Destroy();

    void SwitchGlPolygonMode(GlPolygonMode mode);

    void SetGlClearColor(gl_color color);

    gl_color GetGlClearColor();
}

#endif //INC_05_GUESS_NUMBER_GL_RENDERER_SERVICE_H

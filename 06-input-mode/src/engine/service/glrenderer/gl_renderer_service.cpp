#include "service/glrenderer/gl_renderer_service.h"

static SDL_Window* window_;

void GlRendererService::Render(GlRenderer& gl_renderer) {
  gl_renderer.RenderFrame();
  SDL_GL_SwapWindow(window_);
}

void GlRendererService::SetActiveWindow(SDL_Window* window) {
  window_ = window;
}

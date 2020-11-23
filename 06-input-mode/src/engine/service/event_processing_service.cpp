#include "service/event_processing/event_processing_service.h"

#include "utils/terminal.h"

#define E sdl_event_type_code

inline static bool eq(Uint32 E, Uint32 val) { return E == val; }

inline static bool in(Uint32 E, Uint32 min_in, Uint32 max_ex) {
  return (E < max_ex) && (E >= min_in);
}

static bool IsSdlQuit(Uint32 E) { return eq(E, SDL_EventType::SDL_QUIT); }

static bool IsSdlAppEvent(Uint32 E) {
  return in(E, SDL_QUIT, SDL_DISPLAYEVENT);
}

static bool IsSdlDisplayEvent(Uint32 E) {
  return in(E, SDL_DISPLAYEVENT, SDL_WINDOWEVENT);
}

static bool IsSdlWindowEvent(Uint32 E) {
  return in(E, SDL_WINDOWEVENT, SDL_KEYDOWN);
}

static bool IsSdlKeyboardEvent(Uint32 E) {
  return in(E, SDL_KEYDOWN, SDL_MOUSEMOTION);
}

static bool IsSdlMouseEvent(Uint32 E) {
  return in(E, SDL_MOUSEMOTION, SDL_JOYAXISMOTION);
}

static bool IsSdlJoystickEvent(Uint32 E) {
  return in(E, SDL_JOYAXISMOTION, SDL_CONTROLLERAXISMOTION);
}

static bool IsSdlGameControllerEvent(Uint32 E) {
  return in(E, SDL_CONTROLLERAXISMOTION, SDL_FINGERDOWN);
}

static bool IsSdlTouchEvent(Uint32 E) {
  return in(E, SDL_FINGERDOWN, SDL_DOLLARGESTURE);
}

static bool IsSdlGestureEvent(Uint32 E) {
  return in(E, SDL_DOLLARGESTURE, SDL_CLIPBOARDUPDATE);
}

static bool IsSdlClipboardEvent(Uint32 E) {
  return in(E, SDL_CLIPBOARDUPDATE, SDL_DROPFILE);
}

static bool IsSdlDragAndDropEvent(Uint32 E) {
  return in(E, SDL_DROPFILE, SDL_AUDIODEVICEADDED);
}

static bool IsSdlAudioEvent(Uint32 E) {
  return in(E, SDL_AUDIODEVICEADDED, SDL_SENSORUPDATE);
}

static bool IsSdlSensorEvent(Uint32 E) {
  return in(E, SDL_SENSORUPDATE, SDL_RENDER_TARGETS_RESET);
}

static bool IsSdlRenderEvent(Uint32 E) {
  return in(E, SDL_RENDER_TARGETS_RESET, SDL_USEREVENT);
}

static bool IsSdlUserEvent(Uint32 E) { return eq(E, SDL_USEREVENT); }

static void PlaceholderProcessEventImplementation(std::string_view str, const SDL_Event& sdl_event){
#ifdef PEP_EVENTS_VERBOSE
  Terminal::ReportMsg(">> Event is detected ");
  Terminal::ReportMsg(str);
  Terminal::ReportVal("Timestamp (ms): ", sdl_event.common.timestamp);
#endif
}

static void ProcessQuitEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Quit",sdl_event);
#endif
}

static void ProcessAppEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("App",sdl_event);
#endif
}

static void ProcessDisplayEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Display",sdl_event);
#endif
}

static void ProcessWindowEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Window",sdl_event);
#endif
}

static void ProcessKeyboardEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Keyboard",sdl_event);
#endif
}

static void ProcessMouseEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Mouse",sdl_event);
#endif
}

static void ProcessJoystickEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Joystick",sdl_event);
#endif
}


static void ProcessGameControllerEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("GameController",sdl_event);
#endif
}

static void ProcessTouchEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Touch",sdl_event);
#endif
}

static void ProcessGestureEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Gesture",sdl_event);
#endif
}

static void ProcessClipboardEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Clipboard",sdl_event);
#endif
}

static void ProcessDragAndDropEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Clipboard",sdl_event);
#endif
}

static void ProcessAudioEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Audio",sdl_event);
#endif
}

static void ProcessSensorEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Sensor",sdl_event);
#endif
}

static void ProcessRenderEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("Render",sdl_event);
#endif
}

static void ProcessUserEvent(const SDL_Event& sdl_event){
#ifdef PEP_DEBUG
  PlaceholderProcessEventImplementation("User",sdl_event);
#endif
}

void EventProcessingService::ProcessEvent() {
  SDL_Event sdl_event;

  while (SDL_PollEvent(&sdl_event)) {
    auto e = sdl_event.type;
    if (IsSdlQuit(e))
      ProcessQuitEvent(sdl_event);

    if (IsSdlAppEvent(e))
      ProcessAppEvent(sdl_event);

    if (IsSdlDisplayEvent(e))
      ProcessDisplayEvent(sdl_event);

    if (IsSdlWindowEvent(e))
      ProcessWindowEvent(sdl_event);

    if (IsSdlKeyboardEvent(e))
      ProcessKeyboardEvent(sdl_event);

    if (IsSdlMouseEvent(e))
      ProcessMouseEvent(sdl_event);

    if (IsSdlJoystickEvent(e))
      ProcessJoystickEvent(sdl_event);

    if (IsSdlGameControllerEvent(e))
      ProcessGameControllerEvent(sdl_event);

    if (IsSdlTouchEvent(e))
      ProcessTouchEvent(sdl_event);

    if (IsSdlGestureEvent(e))
      ProcessGestureEvent(sdl_event);

    if (IsSdlClipboardEvent(e))
      ProcessClipboardEvent(sdl_event);

    if (IsSdlDragAndDropEvent(e))
      ProcessDragAndDropEvent(sdl_event);

    if (IsSdlAudioEvent(e))
      ProcessAudioEvent(sdl_event);

    if (IsSdlSensorEvent(e))
      ProcessSensorEvent(sdl_event);

    if (IsSdlRenderEvent(e))
      ProcessRenderEvent(sdl_event);

    if (IsSdlUserEvent(e))
      ProcessUserEvent(sdl_event);
  }
}

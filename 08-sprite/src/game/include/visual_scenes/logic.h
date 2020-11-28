#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#ifndef INC_03_GUESS_NUMBER_G_NUMBER_LOGIC_H
#define INC_03_GUESS_NUMBER_G_NUMBER_LOGIC_H

#include "engine/pep.h"

namespace VisualScenes::Logic {

namespace intro_level {

void OnLoad();

void ExecuteTextWorldLogic();

void Transition();

inline text_world_objects::Stand welcome{{"@@game_title"}, false};

inline const Level data{
    // LEVEL
    {0},
    {{welcome}},
    {intro_level::OnLoad, intro_level::ExecuteTextWorldLogic,
     intro_level::Transition}};
}  // namespace intro_level

namespace bye_level {

void OnLoad();

void ExecuteTextWorldLogic();

void Transition();

inline text_world_objects::Stand bye{
    {{"@@game_title"}},
    false,
    text_world_objects::Stand::Layout::kFixedDefaultBordered,
    0};

inline const Level data{// LEVEL
                        {8},
                        {{bye}},
                        {OnLoad, ExecuteTextWorldLogic, Transition}};
}  // namespace bye_level

namespace common_text_world_objects {

// TODO: to add args firstly add keymaps for input modes

inline text_world_objects::Stand change_render_mode_info{
    {{/*W button*/}}, false, text_world_objects::Stand::Layout::kPureText, 1};

inline text_world_objects::Stand switch_color_info{
    {{/*Up-arrow, Down-arrow*/}},
    false,
    text_world_objects::Stand::Layout::kPureText,
    2};

inline text_world_objects::Stand switch_level_info{
    {{/*Left-arrow, Right-arrow*/}},
    false,
    text_world_objects::Stand::Layout::kPureText,
    3};

inline text_world_objects::Stand mouse_info{
    {{/*mouse swipes?*/}},
    false,
    text_world_objects::Stand::Layout::kPureText,
    4};

inline text_world_objects::Stand touch_info{
    {{/*touch gestures?*/}},
    false,
    text_world_objects::Stand::Layout::kPureText,
    5};

}  // namespace common_text_world_objects

namespace triangle_level {

void OnLoad();

void ExecuteTextWorldLogic();

void Transition();

inline text_world_objects::Stand triangle_info{
    {{/*no*/}}, false, text_world_objects::Stand::Layout::kPureText, 0};

inline visual_world_objects::ViewableTriangle default_triangle{};

inline static std::vector<visual_world_objects::Type> vwo{
    visual_world_objects::Type(default_triangle)};

inline const Level data{
    {{1, 3, 4, 5, 6, 7}},
    {{triangle_info, common_text_world_objects::change_render_mode_info,
      common_text_world_objects::switch_color_info,
      common_text_world_objects::switch_level_info,
      common_text_world_objects::mouse_info,
      common_text_world_objects::touch_info}},
    {OnLoad, ExecuteTextWorldLogic, Transition},
    vwo};

};  // namespace triangle_level

namespace quad_level {

void OnLoad();

void ExecuteTextWorldLogic();

void Transition();

inline text_world_objects::Stand quad_info{
    {{/*no*/}}, false, text_world_objects::Stand::Layout::kPureText, 0};

inline visual_world_objects::ViewableQuad default_quad{};

inline static std::vector<visual_world_objects::Type> vwo{
    visual_world_objects::Type(default_quad)};

inline const Level data{
    {{2, 3, 4, 5, 6, 7}},
    {{quad_info, common_text_world_objects::change_render_mode_info,
      common_text_world_objects::switch_color_info,
      common_text_world_objects::switch_level_info,
      common_text_world_objects::mouse_info,
      common_text_world_objects::touch_info}},
    {OnLoad, ExecuteTextWorldLogic, Transition},
    vwo};

}  // namespace quad_level

namespace texture_level {

void OnLoad();

void ExecuteTextWorldLogic();

void Transition();

inline text_world_objects::Stand tex_info{
    {{/*no*/}}, false, text_world_objects::Stand::Layout::kPureText, 0};

inline visual_world_objects::TexturedQuad default_texture{};

inline static std::vector<visual_world_objects::Type> vwo{
    visual_world_objects::Type(default_texture)};

inline const Level data{
    {{9, 3, 4, 5, 6, 7}},
    {{tex_info, common_text_world_objects::change_render_mode_info,
      common_text_world_objects::switch_color_info,
      common_text_world_objects::switch_level_info,
      common_text_world_objects::mouse_info,
      common_text_world_objects::touch_info}},
    {OnLoad, ExecuteTextWorldLogic, Transition},
    vwo};

}  // namespace texture_level

namespace sprite_level {

void OnLoad();

void ExecuteTextWorldLogic();

void Transition();

inline text_world_objects::Stand tex_info{
    {{/*no*/}}, false, text_world_objects::Stand::Layout::kPureText, 0};

inline visual_world_objects::SpriteQuad explosion{0};

inline static std::vector<visual_world_objects::Type> vwo{
    visual_world_objects::Type(explosion)};

inline const Level data{
    {{10, 3, 4, 5, 6, 7}},
    {{tex_info, common_text_world_objects::change_render_mode_info,
      common_text_world_objects::switch_color_info,
      common_text_world_objects::switch_level_info,
      common_text_world_objects::mouse_info,
      common_text_world_objects::touch_info}},
    {OnLoad, ExecuteTextWorldLogic, Transition},
    vwo};

}  // namespace sprite_level

namespace GlobalVariables {

inline std::vector<VariableDeclaration> declaration{
    // TODO: built-in variables
    {VariableType::kString, "@@game_title", "Visual Demo"},
};

}  // namespace GlobalVariables

namespace Input {

struct Config {
  bool EnableLetters = true;
  bool EnableArrows = true;
  bool EnableMouse = true;
  bool EnableMouseGestures = true;
  bool EnableTouchGestures = true;
};

void SwitchPolygonMode();
void IncreaseColor();
void DecreaseColor();
void GotoPrevLevel();
void GotoNextLevel();
void Quit();

inline static KeyMap common_map{{KeyName::kW, SwitchPolygonMode},
                                {KeyName::kArrowUp, IncreaseColor},
                                {KeyName::kArrowDown, DecreaseColor},
                                {KeyName::kArrowLeft, GotoPrevLevel},
                                {KeyName::kEnter, GotoNextLevel},
                                {KeyName::kArrowRight, GotoNextLevel},
                                {KeyName::kEsc, Quit}};

inline static InputMode common_mode{common_map};
inline static std::vector<InputMode> data{common_mode};

/*
binding_temp mouse_swipe_left{"mouse_lb_swipe_left", "goto_previous_level"};
binding_temp mouse_swipe_right{"mouse_lb_swipe_right", "goto_next_level"};
binding_temp mouse_swipe_up{"mouse_lb_swipe_up", "increase_color"};
binding_temp mouse_swipe_down{"mouse_lb_swipe_down", "decrease_color"};

binding_temp touch_swipe_left{"touch_swipe_left", "goto_previous_level"};
binding_temp touch_swipe_right{"touch_swipe_right", "goto_next_level"};
binding_temp touch_swipe_up{"touch_swipe_up", "increase_color"};
binding_temp touch_swipe_down{"touch_swipe_down", "decrease_color"};
*/

}  // namespace Input

inline const std::vector<Level> visual_scenes{
    intro_level::data,   triangle_level::data, quad_level::data,
    texture_level::data, sprite_level::data,   bye_level::data};

inline static const size_t LAST_LEVEL = 5;

}  // namespace VisualScenes::Logic
#endif  // INC_03_GUESS_NUMBER_G_NUMBER_LOGIC_H

#pragma clang diagnostic pop
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#ifndef INC_03_GUESS_NUMBER_G_NUMBER_LOGIC_H
#define INC_03_GUESS_NUMBER_G_NUMBER_LOGIC_H

#include "engine/pep.h"

// TODO: chaiscript embedded

namespace VisualScenes::Logic {

namespace intro_level {

void OnLoad();

void ExecuteTextWorldLogic();

void Transition();

inline text_world_objects::Stand welcome{{"@@game_title"}};

inline const Level data{
    // LEVEL
    {0},
    {{welcome}},
    {intro_level::OnLoad, intro_level::ExecuteTextWorldLogic,
     intro_level::Transition}};
}  // namespace intro_level

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

bool TransitionCondition();

inline text_world_objects::Stand triangle_info{
    {{/*no*/}}, false, text_world_objects::Stand::Layout::kPureText, 0};

inline visual_world_objects::Viewable default_triangle{};

inline static std::vector<visual_world_objects::Type> vwo{
    visual_world_objects::Type(default_triangle)};

inline const Level data{
    {{1, 3, 4, 5, 6, 7}},
    {{triangle_info, common_text_world_objects::change_render_mode_info,
      common_text_world_objects::switch_color_info,
      common_text_world_objects::switch_level_info,
      common_text_world_objects::mouse_info,
      common_text_world_objects::touch_info}},
    {OnLoad, ExecuteTextWorldLogic, Transition, TransitionCondition},
    vwo};

};  // namespace triangle_level

namespace quad_level {

void OnLoad();

void ExecuteTextWorldLogic();

void Transition();

inline text_world_objects::Stand quad_info{
    {{/*no*/}}, false, text_world_objects::Stand::Layout::kPureText, 0};

inline const Level data{
    {{2, 3, 4, 5, 6, 7}},
    {{quad_info, common_text_world_objects::change_render_mode_info,
      common_text_world_objects::switch_color_info,
      common_text_world_objects::switch_level_info,
      common_text_world_objects::mouse_info,
      common_text_world_objects::touch_info}},
    {OnLoad, ExecuteTextWorldLogic, Transition}};

}  // namespace quad_level

namespace GlobalVariables {

inline std::vector<VariableDeclaration> declaration{
    // TODO: built-in variables
    {VariableType::kString, "@@game_title", "Visual Demo"},
};

}  // namespace GlobalVariables

inline const std::vector<Level> guess_number_levels{
    intro_level::data, triangle_level::data, quad_level::data};

}  // namespace VisualScenes::Logic
#endif  // INC_03_GUESS_NUMBER_G_NUMBER_LOGIC_H

#pragma clang diagnostic pop
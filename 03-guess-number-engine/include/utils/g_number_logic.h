//
// Created by vito on 29.10.20.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#ifndef INC_03_GUESS_NUMBER_G_NUMBER_LOGIC_H
#define INC_03_GUESS_NUMBER_G_NUMBER_LOGIC_H

#include "game_level_logic_processor.h"
#include "level.h"
#include "version.h"

namespace GuessNumber::Logic {

namespace intro_level {
void OnLoad();

void Body();

void Transition();
}  // namespace intro_level

namespace difficulty_level {
void OnLoad();

void Body();

void Transition();
}  // namespace difficulty_level

namespace lobby_level {
void OnLoad();

void Body();

void Transition();
}  // namespace lobby_level

namespace game_core_loop_level {
void OnLoad();

void Body();

void Transition();
}  // namespace game_core_loop_level

namespace game_result_level {
void OnLoad();

void Body();

void Transition();
}  // namespace game_result_level

inline static std::vector<VariableDeclaration> game_global_variables{
    {VariableType::kNaturalInterval, "@diff_interval"},
    {VariableType::kNatural, "@number_max"},
    {VariableType::kNatural, "@attempts_max"},
    {VariableType::kNatural, "@secret_number"},
    {VariableType::kNatural0, "@effort_val"},
    {VariableType::kNatural0, "@attempt_counter"},
    {VariableType::kNatural0, "@attempts_left"},
    {VariableType::kNatural, "@difficulty_level"},
    {VariableType::kBool, "@finished"},
};

inline static std::vector<VariableAssignation>
    game_global_variables_init_values{{"@number_max", "100500"},
                                      {"@diff_interval", "1-3"}};

inline static text_world_objects::Stand welcome{{"@@game_title"}};

inline static const Level intro_lvl{
    // LEVEL
    {0},
    {{welcome}},
    {intro_level::OnLoad, intro_level::Body, intro_level::Transition}};

inline static text_world_objects::Dialog choose_diff{{"@diff_interval"}};

inline static const Level difficulty_lvl{
    // LEVEL
    {{1, 2}},
    {{choose_diff}},
    {difficulty_level::OnLoad, difficulty_level::Body,
     difficulty_level::Transition}};

inline static text_world_objects::Stand number{
    {{"@number_max"}}, false, text_world_objects::Stand::Layout::kPureText, 0};
inline static text_world_objects::Stand attempts{
    {{"@attempts_max"}},
    false,
    text_world_objects::Stand::Layout::kPureText,
    1};
inline static text_world_objects::Stand ready{
    {{/*no*/}}, true, text_world_objects::Stand::Layout::kPureText, 2};
inline static text_world_objects::Stand spoiler{
    {{"@secret_number"}},
    true,
    text_world_objects::Stand::Layout::kFixedDefaultBordered,
    3};

inline static const Level lobby_lvl{
    // LEVEL
    {{3, 4, 5, 6}},
    {{number, attempts, ready, spoiler}},
    {lobby_level::OnLoad, lobby_level::Body, lobby_level::Transition}};

inline static text_world_objects::Dialog guess_dialog{"@effort_val", 0, 1};

inline static text_world_objects::Stand bigger_info{
    /*no args*/ {{}},
    /*no input*/ false, text_world_objects::Stand::Layout::kPureText, 2};

inline static text_world_objects::Stand smaller_info{
    /*no args*/ {{}},
    /*no input*/ false, text_world_objects::Stand::Layout::kPureText, 3};

inline static text_world_objects::Stand guessed_number_info{
    {{"@secret_number"}},
    /*no input*/ true,
    text_world_objects::Stand::Layout::kPureText,
    4};

inline static text_world_objects::Stand tries_left{
    {{"@attempts_left"}},
    /*no input*/ false,
    text_world_objects::Stand::Layout::kPureText,
    5};

inline static text_world_objects::Stand no_more_tries{
    /*no args*/ {{}},
    /*no input*/ true, text_world_objects::Stand::Layout::kPureText, 6};

inline static const Level game_core_loop_lvl{
    // LEVEL
    {{7, 8, 9, 10, 11, 12, 13}},
    {{guess_dialog, bigger_info, smaller_info, guessed_number_info, tries_left,
      no_more_tries}},
    {game_core_loop_level::OnLoad, game_core_loop_level::Body,
     game_core_loop_level::Transition}};

inline static text_world_objects::Stand finished{
    /*no args*/ {{}},
    /*no input*/ false, text_world_objects::Stand::Layout::kPureText, 0};
inline static text_world_objects::Stand spoiler_endgame{
    {{"@secret_number"}},
    /*no input*/ false,
    text_world_objects::Stand::Layout::kPureText,
    1};
inline static text_world_objects::Stand attempts_result{
    {{"@attempt_counter"}},
    /*no input*/ false,
    text_world_objects::Stand::Layout::kPureText,
    2};
inline static text_world_objects::Stand good_result{
    /*no args*/ {{}},
    /*no input*/ true, text_world_objects::Stand::Layout::kPureText, 3};
inline static text_world_objects::Stand bad_result{
    /*no args*/ {{}},
    /*no input*/ true, text_world_objects::Stand::Layout::kPureText, 4};

inline static const Level game_result_lvl{
    // LEVEL
    {{14, 15, 16, 17, 18}},
    {{finished, spoiler_endgame, attempts_result, good_result, bad_result}},
    {game_result_level::OnLoad, game_result_level::Body,
     game_result_level::Transition}};

inline static const std::vector<Level> guess_number_levels{
    intro_lvl, difficulty_lvl, lobby_lvl, game_core_loop_lvl, game_result_lvl};

}  // namespace GuessNumber::Logic
#endif  // INC_03_GUESS_NUMBER_G_NUMBER_LOGIC_H

#pragma clang diagnostic pop
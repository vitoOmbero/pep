#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

namespace ColorMap
{

 inline const int gFirst = 1;
 inline const int gLast = 30;
/**
 * @brief The color enum - Rainbow colors:
 * red/orange/yellow/green/blue/indigo/violet
 * @details Note that some colors are not properly named, but they are close to
 * originals. That color names have "B" or "_l" chars in names.
 */
enum class Color
{
    kNo      = -1, ///< Invisible value
    kUnnamed = 0,  ///< Unsupported value

    k_FIRST_ = gFirst, ///< Iteration value

    kBlack,        ///<#000000	(0,0,0)
    kNavy,         ///<#000080	(0,0,128)
    kBlue,         ///<#0000FF	(0,0,255)
    kGreen,        ///<#008000	(0,128,0)
    kTeal,         ///<#008080	(0,128,128)
    kBlueLight,    ///<####### 	(0,128,255)
    kLime,         ///<#00FF00	(0,255,0)
    kGreenSpringB, ///<#######	(0,255,128) Green_spring is (0,255,127)
    kCyan,         ///<#00FFFF	(0,255,255)
    kIndigo,       ///<#######	(75,0,130)
    kMaroon,       ///<#800000	(128,0,0)
    kPurple,       ///<#800080	(128,0,128)
    kPurpleBlue,   ///<#8000FF	(128,0,255)
    kOlive,        ///<#808000	(128,128,0)
    kGray,         ///<#808080	(128,128,128)
    kSkyBlueDark,  ///<#######	(128,128,255)
    kSilver,       ///<#C0C0C0	(192,192,192)
    kViolet,       ///<####### 	(238,130,238)
    kRed,          ///<#FF0000	(255,0,0)
    kFuchsiaDark,  ///<#FF0080	(255,0,128)
    kMagenta,      ///<#FF00FF	(255,0,255)
    kDarkOrange1B, ///<#FF8000	(255,128,0) DarkOrange1 is (255,127,0)
    kOrange,       ///<#######	(255,165,0)
    kCoralLightD,  ///<#FF8080	(255,128,128)
    kOrchid1L,     ///<#FF80FF	(255,128,255)
    kYellow,       ///<#FFFF00	(255,255,0)
    kKhaki1L,      ///<#FFFF00	(255,255,128)
    kWhite,        ///<#FFFFFF	(255,255,255)

    k_LAST_ = gLast///< Iteration value
};

} // namespace ra_types

#endif // COLOR_H

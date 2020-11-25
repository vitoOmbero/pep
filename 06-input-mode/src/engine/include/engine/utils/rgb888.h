#ifndef RGB888_H
#define RGB888_H

using uchar = unsigned char;

namespace ColorMap
{

/**
 * @brief Storage class for color data.
 */
struct Rgb888
{
    uchar r = 0;
    uchar g = 0;
    uchar b = 0;

    constexpr Rgb888()
    {
        r = 0;
        g = 0;
        b = 0;
    };

    /**
     * Special constructor
     * @param val One value for r,g and b color codes.
     */
    constexpr Rgb888(uchar val)
    {
        r = val;
        g = val;
        b = val;
    };

    /**
     * @brief rgb888 utility constructor
     * @param r_ red value code 0-255
     * @param g_ green value 0-255
     * @param b_ blue value 0-255
     */
    Rgb888(uchar r_, uchar g_, uchar b_)
    {
        r = r_;
        g = g_;
        b = b_;
    };

    bool operator==(const Rgb888& b) const
    {
        return (this->r == b.r && this->g == b.g && this->b == b.b);
    };

    bool operator!=(const Rgb888& b) const
    {
        return (this->r != b.r && this->g != b.g && this->b != b.b);
    };

    bool operator<(const Rgb888& b) const
    {
        return this->r < b.r || this->g < b.g || this->b < b.b;
    };

    Rgb888 operator-(const Rgb888& b) const
    {
        return Rgb888(r - b.r, g - b.g, this->b - b.b);
    };
    /**
     * @brief blue - helper getter
     * @return at least 16bit int
     */
    int blue() const { return static_cast<int>(b); }
    /**
     * @brief green - helper getter
     * @return at least 16bit int
     */
    int green() const { return static_cast<int>(g); }
    /**
     * @brief red - helper getter
     * @return at least 16bit int
     */
    int red() const { return static_cast<int>(r); }
};

} // namespace ra_types
#endif // RGB888_H

#ifndef INC_07_TEXTURED_OBJECTS_TEXTURE_H
#define INC_07_TEXTURED_OBJECTS_TEXTURE_H

#include <string>

struct Texture{
    std::string texture_asset_path;
    bool should_mipmaps_be_generated{true};
};

#endif //INC_07_TEXTURED_OBJECTS_TEXTURE_H

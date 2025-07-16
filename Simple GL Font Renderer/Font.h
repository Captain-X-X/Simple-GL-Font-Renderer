#ifndef FFONT_H
#define FFONT_H
// #define STB_TRUETYPE_IMPLEMENTATION
#include "lib/stb_truetype.h"
#include "maths.h"

struct FontVertex
{
    glm::vec2 position;
    glm::vec2 texCoord;
    glm::vec4 colour;
};

class FFont
{
public:
    FFont(){}
    FFont(const char* fontFile)
    {
        this->loadFont(fontFile);
    }

    unsigned int m_textCapacity;
    unsigned int vao, vbo;
    unsigned int fontShader;
    unsigned int fontTexture;
    stbtt_bakedchar fontCharaterData[96];

    bool loadFont(const char* fontFile, float fontScale=32.0f);
    // inline bool FFont::loadFont()
    // {
    //     return this->loadFont(this->m_fontFile);
    // }
};

#endif
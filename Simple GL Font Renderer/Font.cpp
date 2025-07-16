#include "Font.h"
#include "lib/glad.h"
#include "Shader.h"
#include <cstdio>

#define FONT_VERTEX_SIZE sizeof(Milk::Graphics::FontVertex)
bool FFont::loadFont(const char *fontFile, float fontScale)
{
    // load & create font shader
    fontShader = Shader::CreateShader("fontVert.glsl", "fontFrag.glsl");

    // load truetype file
    unsigned char ttfBuffer[1<<20];
    unsigned char tmpBitmap[512*512];
    FILE* fontFilePtr = fopen(fontFile, "rb");
    if(fontFilePtr == NULL)
    {
        printf("Failed to open/read font file [%s]\n", fontFile);
        return false;
    }
    fread(ttfBuffer, 1, 1<<20, fopen(fontFile, "rb"));
    stbtt_BakeFontBitmap(ttfBuffer, 0, fontScale, tmpBitmap, 512, 512, 32, 96, fontCharaterData);

    // create font opengl texture
    glGenTextures(1, &fontTexture);
    glBindTexture(GL_TEXTURE_2D, fontTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, tmpBitmap);
    glBindTexture(GL_TEXTURE_2D, 0);

    // set the texture in the shader
    Shader::EnableShader(fontShader);
    Shader::setI1("u_fontTexture", fontTexture);

    // setup buffers VAO & VBO
    m_textCapacity = 1024;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(FontVertex) * 6 * m_textCapacity, 0, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(FontVertex), (const void*)(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FontVertex), (const void*)(offsetof(FontVertex, FontVertex::texCoord)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(FontVertex), (const void*)(offsetof(FontVertex, FontVertex::colour)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
    return true;
}
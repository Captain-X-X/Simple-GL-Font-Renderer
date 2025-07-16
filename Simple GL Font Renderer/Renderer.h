#ifndef BATCHRENDERER_H
#define BATCHRENDERER_H
#include <cstdio>
#include "Font.h"
#include "maths.h"

namespace FontRenderer
{
    bool Initilize(FFont* font=nullptr);
    bool Shutdown();
    bool IsRendererOK();

    void Begin();
    void SubmitString(const char* text, float x, float y, glm::vec4 colour);
    void End();
    void Flush();

    FFont* GetFontPtr();
}
#endif // BATCHRENDERER_H
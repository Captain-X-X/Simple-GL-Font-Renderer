#include "Renderer.h"
#include "lib/glad.h"
#include <stdio.h>

#include "Font.h"
#include "Shader.h"

namespace FontRenderer
{
    FFont *m_MainFont = nullptr;
    FontVertex *m_FontDrawData;
    unsigned int m_NumberOfVertices = 0;
    // unsigned int m_NumberOfCharecters = 0x7FFFFFFF;
    bool m_ROK = false;

    bool Initilize(FFont *font)
    {
        if (font == nullptr)
        {
            m_MainFont = new FFont();
            if (m_MainFont->loadFont("stuff/OpenSans-Regular.ttf") == false)
            {
                printf("FontRenderer failed to initilize default font!\n");
                return false;
            }
        }
        else
        {
            m_MainFont = font;
        }
        m_ROK = true;
        return true;
    }
    bool Shutdown()
    {
        if (m_MainFont != nullptr)
        {
            delete m_MainFont;
            return true;
        }
        printf("FontRenderer was not initilized!\n");
        return false;
    }
    bool IsRendererOK()
    {
        return m_ROK;
    }

    void Begin()
    {
        Shader::EnableShader(m_MainFont->fontShader);
        // map buffer
        // glBindVertexArray(m_MainFont->m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_MainFont->vbo);
        m_FontDrawData = (FontVertex *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        // m_NumberOfCharecters=0;
    }
    void SubmitString(const char *text, float x, float y, glm::vec4 colour)
    {
        while (*text)
        {
            if (*text >= 32 && *text < 128)
            {
                stbtt_aligned_quad q;
                stbtt_GetBakedQuad(m_MainFont->fontCharaterData, 512, 512, *text - 32, &x, &y, &q, 1);

                m_FontDrawData->position = glm::vec2(q.x0, q.y0);
                m_FontDrawData->texCoord = glm::vec2(q.s0, q.t0);
                m_FontDrawData->colour = colour;
                m_FontDrawData++;

                m_FontDrawData->position = glm::vec2(q.x1, q.y0);
                m_FontDrawData->texCoord = glm::vec2(q.s1, q.t0);
                m_FontDrawData->colour = colour;
                m_FontDrawData++;

                m_FontDrawData->position = glm::vec2(q.x1, q.y1);
                m_FontDrawData->texCoord = glm::vec2(q.s1, q.t1);
                m_FontDrawData->colour = colour;
                m_FontDrawData++;

                m_FontDrawData->position = glm::vec2(q.x0, q.y1);
                m_FontDrawData->texCoord = glm::vec2(q.s0, q.t1);
                m_FontDrawData->colour = colour;
                m_FontDrawData++;

                m_FontDrawData->position = glm::vec2(q.x0, q.y0);
                m_FontDrawData->texCoord = glm::vec2(q.s0, q.t0);
                m_FontDrawData->colour = colour;
                m_FontDrawData++;

                m_FontDrawData->position = glm::vec2(q.x1, q.y1);
                m_FontDrawData->texCoord = glm::vec2(q.s1, q.t1);
                m_FontDrawData->colour = colour;
                m_FontDrawData++;

                // vData+=6;
                m_NumberOfVertices += 6;
            }
            ++text;
        }
    }
    void End()
    {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        // glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void Flush()
    {
        Shader::EnableShader(m_MainFont->fontShader);
        // setup/bind texture
        glActiveTexture(GL_TEXTURE0 + m_MainFont->fontTexture);
        glBindTexture(GL_TEXTURE_2D, m_MainFont->fontTexture);

        // bind buffers
        glBindVertexArray(m_MainFont->vao);

        // render
        glDrawArrays(GL_TRIANGLES, 0, m_NumberOfVertices);
        m_NumberOfVertices = 0;
        // m_NumberOfCharecters=0;
    }
    FFont *GetFontPtr()
    {
        return m_MainFont;
    }
}
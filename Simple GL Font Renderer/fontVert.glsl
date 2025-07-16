#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aColour;

out vec2 texCoord;
out vec4 texColour;

uniform mat4 viewMatrix=mat4(1.0f);

void main()
{
   gl_Position = viewMatrix * vec4(aPos, 0.0, 1.0f);
   texCoord=aTexCoord;
   texColour=aColour;
}
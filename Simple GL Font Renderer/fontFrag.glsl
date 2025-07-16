#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec4 texColour;

uniform sampler2D u_fontTexture;

void main()
{
	vec4 sample = vec4(1.0, 1.0, 1.0, texture(u_fontTexture, texCoord).r);
	FragColor = texColour * sample;
};
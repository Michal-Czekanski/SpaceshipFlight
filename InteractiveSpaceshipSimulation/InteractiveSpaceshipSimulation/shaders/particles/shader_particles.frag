#version 430 core
layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 brightColor;

in vec2 interpTexCoord;
flat in vec4 particleColor;

uniform sampler2D textureSampler;

// --- main --- ///
void main()
{
	fragColor = (texture(textureSampler, interpTexCoord) * particleColor);
    brightColor = vec4(0, 0, 0, 0);
}

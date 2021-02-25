#version 430 core
layout(location = 3) in vec4 instVertexColor;
layout (location = 0) out vec4 fragColor;

in vec2 interpTexCoord;

uniform sampler2D textureSampler;

// --- main --- ///
void main()
{
	fragColor = vec4(texture(textureSampler, interpTexCoord) * instVertexColor);
}

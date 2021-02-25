#version 430 core
layout(location = 2) in vec4 instVertexColor;
layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 brightColor;

in vec2 interpTexCoord;

uniform sampler2D textureSampler;

// --- main --- ///
void main()
{
	//fragColor = (texture(textureSampler, interpTexCoord) * instVertexColor);
    fragColor = texture(textureSampler, interpTexCoord);
    brightColor = vec4(0, 0, 0, 1);
}

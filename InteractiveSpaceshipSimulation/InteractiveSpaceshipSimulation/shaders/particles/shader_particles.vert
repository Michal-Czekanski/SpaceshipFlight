#version 430 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec4 instParticleColor;
layout(location = 3) in mat4 instParticleModelMatrix; // layouts 3,4,5,6 are taken for this matrix

uniform mat4 cameraMatrix;
uniform mat4 perspectiveMatrix;
uniform float particleSize = 1.0f;

out vec2 interpTexCoord;
flat out vec4 particleColor;

void main()
{
	gl_Position = perspectiveMatrix * cameraMatrix * instParticleModelMatrix
    * vec4(vertexPosition, 1.0f);
    interpTexCoord = vertexTexCoord;
    particleColor = instParticleColor;
}

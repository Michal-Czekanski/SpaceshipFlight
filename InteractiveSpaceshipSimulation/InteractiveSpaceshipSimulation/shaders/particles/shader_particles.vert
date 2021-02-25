#version 430 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec3 instParticleCenterWrld;

uniform vec3 cameraUp;
uniform vec3 cameraRight;
uniform mat4 cameraMatrix;
uniform mat4 perspectiveMatrix;

uniform float particleSize = 1.0f;

out vec2 interpTexCoord;

void main()
{
    vec3 vertexPositionWorld = instParticleCenterWrld
    + cameraRight   * vertexPosition.x * particleSize
    + cameraUp      * vertexPosition.y * particleSize;
	gl_Position = perspectiveMatrix * cameraMatrix * vec4(vertexPositionWorld, 1.0f);
    interpTexCoord = vertexTexCoord;
}

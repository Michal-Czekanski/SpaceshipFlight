#version 430 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in mat4 instanceModelMatrix;

uniform mat4 perspectiveMatrix;
uniform mat4 cameraMatrix;

out vec3 interpNormal;
out vec3 fragPos;
out vec3 fragShipPos;
out vec2 interpTexCoord;

void main()
{
	mat4 instanceModelViewProjectionMatrix = perspectiveMatrix * cameraMatrix * instanceModelMatrix;
	gl_Position = instanceModelViewProjectionMatrix * vec4(vertexPosition, 1.0);
	interpNormal = (instanceModelMatrix * vec4(vertexNormal, 0.0)).xyz;
	fragPos = (instanceModelMatrix*vec4(vertexPosition,1)).xyz;
    interpTexCoord = vertexTexCoord;
}

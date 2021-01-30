#version 430 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec3 vertexNormal;

layout(location = 7) in vec3 vertexTangent;
layout(location = 8) in vec3 vertexBitangent;

uniform mat4 modelMatrix;

uniform mat4 modelViewProjectionMatrix;

out vec3 interpNormal;
out vec3 fragPos;
out vec3 fragShipPos;
out vec2 interpTexCoord;

out vec3 lightDirTS_ship;
out vec3 lightDirsTS_star[3];
out vec3 viewDirTS;

uniform vec3 shipPos;
const int starsCount = 3;
uniform vec3[starsCount] starsPos;

uniform vec3 cameraPos;

void main()
{
    vec3 lightDir_ship = normalize(vertexPosition - shipPos);
    vec3 lightDir_stars[starsCount];
    for(int i = 0; i < starsCount; i++ )
    {
        lightDir_stars[i] = normalize(vertexPosition - starsPos[i]);
    }

	gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
	interpNormal = (modelMatrix * vec4(vertexNormal, 0.0)).xyz;
	fragPos = (modelMatrix*vec4(vertexPosition,1)).xyz;
    interpTexCoord = vertexTexCoord;

    vec3 vertPos = (modelMatrix * vec4(vertexPosition, 1.0)).xyz;

    vec3 worldNormal = (modelMatrix * vec4(vertexNormal, 0)).xyz;
    vec3 worldTangent = (modelMatrix * vec4(vertexTangent, 0)).xyz;
    vec3 worldBitangent = (modelMatrix * vec4(vertexBitangent, 0)).xyz;

    mat3 TBN = transpose(mat3(worldTangent, worldBitangent, worldNormal));
    vec3 viewDir = normalize(cameraPos - vertPos);

    viewDirTS = viewDir * TBN;
    lightDirTS_ship = lightDir_ship * TBN;
    lightDirsTS_star[0] = lightDir_stars[0] * TBN;
    lightDirsTS_star[1] = lightDir_stars[1] * TBN;
    lightDirsTS_star[2] = lightDir_stars[2] * TBN;
}

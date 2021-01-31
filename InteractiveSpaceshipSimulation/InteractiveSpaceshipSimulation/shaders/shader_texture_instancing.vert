#version 430 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in mat4 instanceModelMatrix; // 3,4,5,6

layout(location = 7) in vec3 vertexTangent;
layout(location = 8) in vec3 vertexBitangent;

uniform mat4 perspectiveMatrix;
uniform mat4 cameraMatrix;

uniform vec3 cameraPos;

out vec3 fragPos;
out vec3 fragShipPos;
out vec2 interpTexCoord;

out vec3 lightDirTS_ship;
out vec3 lightDirsTS_star[3];
out vec3 viewDirTS;

uniform vec3 shipPos;
const int starsCount = 3;
uniform vec3[starsCount] starsPos;




void main()
{
    mat4 instanceModelViewProjectionMatrix = perspectiveMatrix * cameraMatrix * instanceModelMatrix;
    
	gl_Position = instanceModelViewProjectionMatrix * vec4(vertexPosition, 1.0);
	fragPos = (instanceModelMatrix*vec4(vertexPosition,1)).xyz;
    interpTexCoord = vertexTexCoord;

    vec3 vertPos = fragPos;

    vec3 lightDir_ship = normalize(shipPos - vertPos);
    vec3 lightDir_stars[starsCount];
    for(int i = 0; i < starsCount; i++ )
    {
        lightDir_stars[i] = normalize(starsPos[i] - vertPos);
    }

    vec3 worldNormal = (instanceModelMatrix * vec4(vertexNormal, 0)).xyz;
    vec3 worldTangent = (instanceModelMatrix * vec4(vertexTangent, 0)).xyz;
    vec3 worldBitangent = (instanceModelMatrix * vec4(vertexBitangent, 0)).xyz;

    mat3 TBN = transpose(mat3(worldTangent, worldBitangent, worldNormal));
    vec3 viewDir = normalize(cameraPos - vertPos);

    viewDirTS = TBN * viewDir;
    lightDirTS_ship = TBN * lightDir_ship;
    lightDirsTS_star[0] = TBN * lightDir_stars[0];
    lightDirsTS_star[1] = TBN * lightDir_stars[1];
    lightDirsTS_star[2] = TBN * lightDir_stars[2];
}

#version 430 core
layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 brightColor;

in vec2 interpTexCoord;

uniform sampler2D textureSampler;
uniform sampler2D normalSampler;

in vec3 viewDirTS;

in vec3 lightDirTS_ship;
in vec3 lightDirsTS_star[3];

in vec3 fragPos;

uniform vec3 cameraPos;

uniform vec3 shipPos;
uniform vec3 shipDirection;
uniform float shipLightConeHeight;
uniform float shipLightConeRadius;
uniform vec3 shipLightColor;
uniform float shipLightStr = 50.0f;

const int starsCount = 3;
uniform vec3[starsCount] starsPos;
uniform float[starsCount] starsLightStr;
uniform vec3[starsCount] starsLightCol;

const float ambientLightIntensity = 0.01;
const int brilliancy = 10;
// --- Func defs --- ///
bool isPointInShipLightRange(vec3 point, vec3 shipPos, vec3 shipDirection, float shipLightConeHeight, float shipLightConeRadius)
{
	float cone_dist = dot(point - shipPos, shipDirection); //  project point onto shipDirection to find the point's distance along the shipDirection axis from shipPosition

	if(cone_dist < 0 || cone_dist > shipLightConeHeight)
	{
		return false;
	}

	float cone_radiusAtPoint = (cone_dist / shipLightConeHeight) * shipLightConeRadius; // calculate the cone radius at given point along the shipDirection axis
	float orth_distance = length((point - shipPos) - cone_dist * shipDirection); // calculate the point's orthogonal distance from the shipDirection axis
	bool is_point_inside_cone = (orth_distance < cone_radiusAtPoint); //  compare point's orthogonal distance against the cone radius

	return is_point_inside_cone;
}

float calculateAttenuation(vec3 lightPos, vec3 fragPos, float maxAttenuationDist)
{
	vec3 toLight = lightPos - fragPos;
	float distFromL = length(toLight);
	return clamp(maxAttenuationDist / (distFromL*distFromL), 0.0, 1.0);
}

float calculateDiffuseIntensity(vec3 normal, vec3 lightDir)
{
	return max(dot(normal, lightDir), 0);
}

vec3 calculateDiffuseColor(float intensity, vec3 objectColor)
{
	return intensity * objectColor;
}

float calculateSpecularIntensity(vec3 viewDirection, vec3 lightDir, vec3 normal, int brilliancy)
{
	vec3 reflectedLightDir = reflect(-normalize(lightDir), normal);

	return 0.3 * pow(max(0, dot(reflectedLightDir, viewDirection)), brilliancy); // 0.1 for TEST
}

vec3 calculateSpecularColor(float intensity, vec3 color)
{
	return intensity * color;
}

void calculateBrightColor(vec3 color, vec3 threshold)
{
    float brightness = dot(color, threshold);
    if(brightness > 1.0)
        brightColor = vec4(color, 1.0);
    else
        brightColor = vec4(0.0, 0.0, 0.0, 1.0);
}

// --- main --- ///
void main()
{
    vec3 color = texture2D(textureSampler, interpTexCoord).rgb;
	vec3 normal = texture2D(normalSampler, interpTexCoord).rgb; // Wczytanie wektorow normalnych z tekstury
    normal = normalize(normal * 2 - 1); // Przeksztalcenie z [0, 1] do [-1, 1]
    vec3 viewDir = normalize(viewDirTS);

	vec3 specularColor = vec3(0, 0, 0);
	vec3 diffuseColor = vec3(0, 0, 0);
	vec3 ambientColor = color * ambientLightIntensity;

	// Light from ship
	if(isPointInShipLightRange(fragPos, shipPos, shipDirection, shipLightConeHeight, shipLightConeRadius))
	{
        vec3 shipLightDir = normalize(lightDirTS_ship);
		float shipLightAttenuation = calculateAttenuation(shipPos, fragPos, shipLightStr);
		diffuseColor += shipLightAttenuation * calculateDiffuseColor(calculateDiffuseIntensity(normal, shipLightDir), color);
		specularColor += shipLightAttenuation * calculateSpecularColor(calculateSpecularIntensity(viewDir, shipLightDir, normal, brilliancy), shipLightColor);
	}

	// Light from stars
    for(int i = 0; i < starsCount; i++ )
    {
        vec3 starLightDir = normalize(lightDirsTS_star[i]);
        float starLightAttenuation = calculateAttenuation(starsPos[i], fragPos, starsLightStr[i]);
        float starDiffuseIntensity = calculateDiffuseIntensity(normal, starLightDir);
        diffuseColor += starLightAttenuation * calculateDiffuseColor(starDiffuseIntensity, color);
        if(starDiffuseIntensity > 0)
    	{
    		// Prevent specular light from appearing on the back sides without light.
    		specularColor += starLightAttenuation *
            calculateSpecularColor(calculateSpecularIntensity(viewDir, starLightDir, normal, brilliancy), starsLightCol[i]);
    	}
    }

	fragColor = vec4(ambientColor + diffuseColor + specularColor , 1.0f);

    vec3 brightColorThreshold = vec3(0.1, 0.1, 0.1);
    calculateBrightColor(fragColor.rgb, brightColorThreshold);
}

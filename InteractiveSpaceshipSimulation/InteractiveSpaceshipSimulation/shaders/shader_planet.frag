#version 430 core

uniform vec3 objectColor;

uniform vec3 cameraPos;

uniform vec3 shipPos;
uniform vec3 shipDirection;
uniform float shipLightConeHeight;
uniform float shipLightConeRadius;

uniform vec3 shipLightColor;

in vec3 interpNormal;
in vec3 fragPos;
in int pointInShipLightRange;


out vec4 fragColor;

float ambientLightIntensity = 0.2;

int brilliancy = 10;

float maxAttentuationDist = 10.f; // Distance from light source at which light is at maximum intensity



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

float calculateAttentuation(vec3 lightPos, vec3 fragPos, float maxAttentuationDist)
{
	vec3 toLight = lightPos - fragPos;
	float distFromL = length(toLight);
	return clamp(maxAttentuationDist / distFromL, 0.0, 1.0);
}

float calculateDiffuseIntensity(vec3 normal, vec3 lightDir)
{
	return max(dot(normal, -lightDir), 0);
}

vec3 calculateDiffuseColor(float intensity, vec3 objectColor)
{
	return intensity * objectColor;
}

float calculateSpecularIntensity(vec3 cameraPos, vec3 fragPos, vec3 lightDir, vec3 normal, int brilliancy)
{
	vec3 viewDirection = normalize(cameraPos - fragPos);
	vec3 reflectedLightDir = reflect(-lightDir, normal);

	return pow(max(0, dot(reflectedLightDir, viewDirection)), brilliancy);
}

vec3 calculateSpecularColor(float intensity, vec3 color)
{
	return intensity * color;
}

void main()
{
	vec3 shipLightDir = normalize(fragPos-shipPos);
	vec3 normal = normalize(interpNormal);

	vec3 specularColor = vec3(0, 0, 0);
	vec3 diffuseColor = vec3(0, 0, 0);
	vec3 ambientColor = objectColor * ambientLightIntensity;

	// Light from ship
	if(isPointInShipLightRange(fragPos, shipPos, shipDirection, shipLightConeHeight, shipLightConeRadius))
	{
		float shipLightAttentuation = calculateAttentuation(shipPos, fragPos, maxAttentuationDist);
		diffuseColor += shipLightAttentuation * calculateDiffuseColor(calculateDiffuseIntensity(normal, shipLightDir), objectColor);
		specularColor += shipLightAttentuation * calculateSpecularColor(calculateSpecularIntensity(cameraPos, fragPos, shipLightDir, normal, brilliancy), shipLightColor);
	}
	
	fragColor = vec4(ambientColor + diffuseColor + specularColor , 1.0f);
}

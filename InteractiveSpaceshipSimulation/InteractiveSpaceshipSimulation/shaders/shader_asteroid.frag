#version 430 core

uniform vec3 objectColor;

uniform vec3 cameraPos;

uniform vec3 shipPos;
uniform vec3 shipDirection;
uniform float shipLightConeHeight;
uniform float shipLightConeRadius;

in vec3 interpNormal;
in vec3 fragPos;
in int pointInShipLightRange;


out vec4 fragColor;

float ambientLightIntensity = 0.2;

int brilliancy = 10;


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


float calculateDiffuse(vec3 normal, vec3 lightDir)
{
	return max(dot(normal, -lightDir), 0);
}

float calculateSpecular(vec3 cameraPos, vec3 fragPos, vec3 lightDir, vec3 normal, int brilliancy)
{
	vec3 viewDirection = normalize(cameraPos - fragPos);
	vec3 reflectedLightDir = reflect(-lightDir, normal);

	return pow(max(0, dot(reflectedLightDir, viewDirection)), brilliancy);
}

vec3 phongLight(vec3 cameraPos, vec3 fragPos, vec3 lightDir, vec3 normal, int brilliancy, vec3 objectColor, float ambientLightIntensity)
{
	float diffusedLightIntensity = calculateDiffuse(normal, lightDir);

	float specularLightIntensity = calculateSpecular(cameraPos, fragPos, lightDir, normal, brilliancy);
	return mix(objectColor, objectColor * diffusedLightIntensity + vec3(1) * specularLightIntensity, 1.0 - ambientLightIntensity);
}

void main()
{
	vec3 shipLightDir = normalize(fragPos-shipPos);
	vec3 normal = normalize(interpNormal);

	if(isPointInShipLightRange(fragPos, shipPos, shipDirection, shipLightConeHeight, shipLightConeRadius))
	{
		fragColor.rgb = phongLight(cameraPos, fragPos, shipLightDir, normal, brilliancy, objectColor, ambientLightIntensity);
		fragColor.a = 1.0;
	}
	else
	{
		fragColor = vec4(objectColor * ambientLightIntensity, 1.0);
	}
}

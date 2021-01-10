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

void main()
{
	vec3 lightDir = normalize(fragPos-shipPos);
	vec3 normal = normalize(interpNormal);
	float diffuse = max(dot(normal, -lightDir), 0.0);

	if(isPointInShipLightRange(fragPos, shipPos, shipDirection, shipLightConeHeight, shipLightConeRadius))
	{
		vec3 V = normalize(cameraPos-fragPos);
		vec3 R = reflect(-lightDir,normal);
		float specular = pow(max(0,dot(R,V)),10);
		float ambient = 0.1;
		fragColor.rgb = mix(objectColor, objectColor * diffuse + vec3(1) * specular, 1.0 - ambient);
		fragColor.a = 1.0;
	}
	else
	{
		//fragColor = vec4(objectColor * diffuse, 1.0);
		fragColor = vec4(1, 0, 0, 1);
	}
}

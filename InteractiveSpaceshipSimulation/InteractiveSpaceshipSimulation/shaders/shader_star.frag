#version 430 core

uniform vec3 objectColor;
uniform vec3 starPos;

in vec3 interpNormal;
in vec3 fragPos;

out vec4 fragColor;

void main()
{
	vec3 normal = normalize(interpNormal);

    vec3 lightDir = normalize(starPos-fragPos);
	float diffuse = max(dot(normal, -lightDir), 0.0);
	fragColor = vec4(objectColor * diffuse, 1.0);
}

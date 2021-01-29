#version 430 core

uniform vec3 objectColor;
uniform vec3 starPos;
uniform sampler2D textureSampler;

in vec3 interpNormal;
in vec3 fragPos;
in vec2 interpTexCoord;


out vec4 fragColor;


void main()
{
	vec3 normal = normalize(interpNormal);

  vec3 lightDir = normalize(starPos-fragPos);
	float diffuse = max(dot(normal, -lightDir), 0.0);

	vec3 color = texture2D(textureSampler, interpTexCoord).rgb;
	fragColor = vec4(color * diffuse, 1.0);
}

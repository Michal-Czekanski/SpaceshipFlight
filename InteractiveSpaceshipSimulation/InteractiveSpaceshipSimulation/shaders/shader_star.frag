#version 430 core
layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 brightColor;

uniform vec3 objectColor;
uniform vec3 starPos;

in vec3 interpNormal;
in vec3 fragPos;

void calculateBrightColor(vec3 color, vec3 threshold)
{
    float brightness = dot(color, threshold);
    if(brightness > 1.0)
        brightColor = vec4(color, 1.0);
    else
        brightColor = vec4(0.0, 0.0, 0.0, 1.0);
}

void main()
{
	vec3 normal = normalize(interpNormal);

    vec3 lightDir = normalize(starPos-fragPos);
	float diffuse = max(dot(normal, -lightDir), 0.0);
	fragColor = vec4(objectColor * diffuse, 1.0);

    vec3 brightColorThreshold = vec3(vec3(1.0, 1.0, 1.0));
    calculateBrightColor(fragColor.rgb, brightColorThreshold);
}

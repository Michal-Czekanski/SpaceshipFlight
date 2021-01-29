#version 430 core
layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 brightColor;

uniform vec3 objectColor;
uniform vec3 starPos;
uniform sampler2D textureSampler;

in vec3 interpNormal;
in vec3 fragPos;

in vec2 interpTexCoord;

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

	vec3 color = 2*texture2D(textureSampler, interpTexCoord).rgb;
	fragColor = vec4(color * diffuse, 1.0);

    vec3 brightColorThreshold = vec3(vec3(5.0, 0.8, 0.3));
    calculateBrightColor(fragColor.rgb, brightColorThreshold);
}

#pragma once

#include "graphics_techniques/particles/Particle.h"

class ParticleGenerator
{
public:
private:
	const int maxParticles;
	Particle* particles;
	glm::vec3 posInParent;
	glm::vec3 generationDir;
	float generationAngle;
	unsigned int programId;
	unsigned int textureId;
};
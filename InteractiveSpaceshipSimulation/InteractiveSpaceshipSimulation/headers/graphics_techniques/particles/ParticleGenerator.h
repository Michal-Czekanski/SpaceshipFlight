#pragma once

#include "glew.h"
#include "freeglut.h"
#include "graphics_techniques/particles/Particle.h"
#include <vector>

class ParticleGenerator
{
public:
	ParticleGenerator(glm::vec3 posInParent, glm::vec3 parentPosition, glm::vec3 generationDir, glm::quat parentRotation,
		const int maxParticles,	float generationAngle, unsigned int programId, unsigned int textureId);
private:
	const int maxParticles;
	std::vector<Particle> particles;
	glm::vec3 posInParent;
	glm::vec3 generationDir;
	glm::vec3 worldPosition;
	float generationAngle;
	unsigned int programId;
	unsigned int textureId;

	GLuint vao;
	GLuint instanceModelMatrixesBuffer;

	void initVAO();


	const float billboard_vertexes[3 * 4] = {
	 -0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 -0.5f, 0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	};
};
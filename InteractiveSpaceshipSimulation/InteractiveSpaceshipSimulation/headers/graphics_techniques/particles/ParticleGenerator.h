#pragma once

#include "glew.h"
#include "freeglut.h"
#include "graphics_techniques/particles/Particle.h"
#include <vector>
#include "utils/Texture.h"
#include "utils/Calculations.h"

class ParticleGenerator
{
public:
	ParticleGenerator(glm::vec3 posInParent, glm::vec3 generationDir,
		const int maxParticles,	float generationAngle, unsigned int programId, unsigned int textureId,
		float particlesPerMs=0.5f);
	void startGeneration();
	void stopGeneration();
	void update(glm::vec3 parentPos, glm::quat parentRotation,
		glm::vec3 cameraUp, glm::vec3 cameraRight, glm::vec3 cameraFront);
	void draw(glm::vec3 parentPos, glm::quat parentRotation,
		glm::mat4 cameraMatrix, glm::mat4 perspectiveMatrix);

private:
	const int maxParticles;
	/// <summary>
	/// How many particles per millisecond
	/// </summary>
	float particlesPerMs;
	std::vector<Particle> particles;
	glm::vec3 posInParent;
	glm::vec3 generationDir;
	glm::vec3 worldPosition;

	glm::vec3 particleRight;
	glm::vec3 particleTop;
	glm::vec3 particleForward;

	glm::quat particleRotation;

	float generationAngle;
	unsigned int programId;
	unsigned int textureId;
	unsigned int lastAliveParticle;
	glm::vec3 calculateParticleVelocity();

	void updateParticleDirections(glm::vec3 cameraUp, glm::vec3 cameraRight, glm::vec3 cameraFront);

	void loadInstanceDataToBuffers();
	bool isGenerating;

	GLuint vao;
	GLuint instanceParticleModelMatrixVBO;
	GLuint instanceColorsVBO;

	void initVAO();
	void updateGenerationDir(glm::quat parentRotation);
	/// <summary>
	/// Searches particles container for index of first dead particle.
	/// </summary>
	unsigned int findDeadParticle();

	void createNewParticles();

	unsigned int particlesCount;


	const float billboard_vertexes[3 * 6] = {
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	const float texture_coords[2 * 6] = {
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};
};

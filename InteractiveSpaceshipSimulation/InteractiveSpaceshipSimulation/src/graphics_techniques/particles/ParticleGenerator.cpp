#include "graphics_techniques/particles/ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(glm::vec3 posInParent, glm::vec3 generationDir, 
	const int maxParticles, float generationAngle, 
	unsigned int programId, unsigned int textureId,
	unsigned int particlesPerMs):
	posInParent(posInParent), worldPosition(posInParent), maxParticles(maxParticles),
	generationAngle(generationAngle), programId(programId), textureId(textureId), generationDir(generationDir),
	particles(), particlesPerMs(particlesPerMs), isGenerating(false)
{
	initVAO();
}

void ParticleGenerator::startGeneration()
{
	particles.clear();
	isGenerating = true;
	for (int i = 0; i < maxParticles; i++)
	{
		particles[i] = Particle();
	}
}

void ParticleGenerator::stopGeneration()
{
	isGenerating = false;
}

void ParticleGenerator::update(glm::vec3 parentPos, glm::quat parentRotation)
{
	worldPosition = parentPos + posInParent;
	updateGenerationDir(parentRotation);

	if (isGenerating)
	{
		createNewParticles();
	}

	for (Particle& particle : particles)
	{
		particle.update();
	}
}


void ParticleGenerator::updateGenerationDir(glm::quat parentRotation)
{
	generationDir = parentRotation * generationDir * glm::inverse(parentRotation);
}

unsigned int ParticleGenerator::findDeadParticle()
{
	for (int i = lastAliveParticle; i < maxParticles; i++)
	{
		if (!particles[i].isAlive())
		{
			return i;
		}
	}

	for (int i = 0; i < lastAliveParticle; i++)
	{
		if (!particles[i].isAlive())
		{
			return i;
		}
	}

	return 0;
}

void ParticleGenerator::createNewParticles()
{
	lastAliveParticle = findDeadParticle();
	int newParticlesCount = Time::getDeltaTime() * particlesPerMs;

	for (int i = 0; i < newParticlesCount; i++)
	{
		particles[(lastAliveParticle + i) % maxParticles] = Particle(worldPosition, glm::vec4(0, 0, 0, 1), 
			calculateParticleVelocity());
	}
}


glm::vec3 ParticleGenerator::calculateParticleVelocity()
{
	// TODO - use generation angle to calculate
	return generationDir;
}

void ParticleGenerator::initVAO()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// vertexPosition
	GLuint billboardVBO;
	glGenBuffers(1, &billboardVBO);
	glBindBuffer(GL_ARRAY_BUFFER, billboardVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(billboard_vertexes), billboard_vertexes, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// vertexTexCoord
	GLuint textCoordVBO;
	glGenBuffers(1, &textCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coords), texture_coords, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// instVertexColor
	glGenBuffers(1, &instanceColorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceColorsVBO);
	glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(float), NULL, GL_STREAM_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glVertexAttribDivisor(1, 1);

	// instParticleCenterWrld
	glGenBuffers(1, &instanceParticleCenter);
	glBindBuffer(GL_ARRAY_BUFFER, instanceParticleCenter);
	glBufferData(GL_ARRAY_BUFFER, maxParticles * 3 * sizeof(float), NULL, GL_STREAM_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glVertexAttribDivisor(3, 1);

	glBindVertexArray(0);
}

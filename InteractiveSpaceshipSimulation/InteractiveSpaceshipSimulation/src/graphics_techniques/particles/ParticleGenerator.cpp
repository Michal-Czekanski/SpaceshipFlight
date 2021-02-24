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

	//
	GLuint billboardVBO;
	glGenBuffers(1, &billboardVBO);
	glBindBuffer(GL_ARRAY_BUFFER, billboardVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(billboard_vertexes), billboard_vertexes, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//
	GLuint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(float), NULL, GL_STREAM_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//
	glGenBuffers(1, &instanceModelMatrixesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, instanceModelMatrixesBuffer);
	glBufferData(GL_ARRAY_BUFFER, maxParticles * sizeof(glm::mat4), NULL, GL_STREAM_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glBindVertexArray(0);
}

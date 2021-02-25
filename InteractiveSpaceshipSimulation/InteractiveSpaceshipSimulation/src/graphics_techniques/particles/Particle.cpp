#include "graphics_techniques/particles/Particle.h"

Particle::Particle(): size(0.0f), distFromCamera(-1.0f)
{
	life = minLife;
}

Particle::Particle(glm::vec3 position, glm::vec4 color, glm::vec3 velocity, glm::vec3 cameraPos, float size):
	position(position), color(color), velocity(velocity), size(size)
{
	life = maxLife;
	distFromCamera = glm::fastDistance(position, cameraPos);
}

Particle::Particle(const Particle& p) :
	position(p.position), color(p.color), velocity(p.velocity), life(p.life), size(p.size), distFromCamera(p.distFromCamera)
{
	
}

Particle Particle::operator=(const Particle& p)
{
	if (this == &p) {
		return *this;
	}

	position = p.position;
	color = p.color;
	velocity = p.velocity;
	life = p.life;
	size = p.size;
	distFromCamera = p.distFromCamera;
}

bool Particle::operator<(const Particle& other) const
{
	// Sort in reverse -> far particles drawn first
	return distFromCamera > other.distFromCamera;
}

bool Particle::isAlive()
{
	return life > minLife;
}

void Particle::update(glm::vec3 cameraPos)
{
	if (isAlive())
	{
		float deltaTime = Time::getDeltaTimeSec();
		life -= deltaTime;
		color.a = life / maxLife;
		position += velocity * deltaTime;
		distFromCamera = glm::fastDistance(position, cameraPos);
	}
	else {
		distFromCamera = -1.0f;
	}
}

glm::vec3 Particle::getPosition()
{
	return position;
}

glm::vec4 Particle::getColor()
{
	return color;
}

glm::vec3 Particle::getVelocity()
{
	return velocity;
}

float Particle::getLife()
{
	return life;
}

float Particle::getSize()
{
	return size;
}

float Particle::getDistanceFromCamera()
{
	return distFromCamera;
}

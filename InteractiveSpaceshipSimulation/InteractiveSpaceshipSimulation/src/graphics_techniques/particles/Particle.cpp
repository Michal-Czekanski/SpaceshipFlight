#include "graphics_techniques/particles/Particle.h"

Particle::Particle(): size(0.0f)
{
	life = minLife;
}

Particle::Particle(glm::vec3 position, glm::vec4 color, glm::vec3 velocity, float size):
	position(position), color(color), velocity(velocity), size(size)
{
	life = maxLife;
}

Particle::Particle(const Particle& p) :
	position(p.position), color(p.color), velocity(p.velocity), life(p.life), size(p.size)
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
}

bool Particle::isAlive()
{
	return life > minLife;
}

void Particle::update()
{
	float deltaTime = Time::getDeltaTimeSec();
	if (isAlive())
	{
		life -= deltaTime;
		color.a -= deltaTime;
		position += velocity * deltaTime;
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

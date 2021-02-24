#include "graphics_techniques/particles/Particle.h"

Particle::Particle()
{
	life = minLife;
}

Particle::Particle(glm::vec3 position, glm::vec4 color, glm::vec3 velocity):
	position(position), color(color), velocity(velocity)
{
	life = maxLife;
}

Particle::Particle(const Particle& p) :
	position(p.position), color(p.color), velocity(p.velocity), life(p.life)
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

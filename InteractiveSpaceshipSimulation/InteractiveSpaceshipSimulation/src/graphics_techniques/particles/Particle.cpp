#include "graphics_techniques/particles/Particle.h"

Particle::Particle(glm::vec3 position, glm::vec4 color, glm::vec3 velocity): 
	position(position), color(color), velocity(velocity)
{
	life = maxLife;
}

bool Particle::isAlive()
{
	return life > minLife;
}

#include "Particle.h"

using namespace P6;

P6Particle::P6Particle() {}

P6Particle::P6Particle(P6::VectorClass position, VectorClass velocity, VectorClass acceleration)
{
    this->position  = position;
    this->velocity  = velocity;
    this->acceleration = acceleration;
}

void P6Particle::updatePosition(float time)
{
	this->position = this->position + (this->velocity * time) + ((this->acceleration * time * time) * (1.0f / 2.0f));
}

void P6Particle::Update(float time)
{
	this->updatePosition(time);
	//this->updateVelocity(time);
}
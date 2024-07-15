#include "P6Particle.h"

using namespace P6;

P6Particle::P6Particle() {}

P6Particle::P6Particle(P6::VectorClass position, VectorClass velocity, VectorClass acceleration)
{
    this->position  = position;
    this->velocity  = velocity;
    this->acceleration = acceleration;
}

void P6Particle::UpdatePosition(float time)
{
	this->position = this->position + (this->velocity * time) + ((this->acceleration * time * time) * (1.0f / 2.0f));
}

void P6Particle::Update(float time)
{
	this->UpdatePosition(time);
	this->UpdateVelocity(time);

    this->ResetForce();
}

void P6Particle::UpdateVelocity(float time)
{
    this->acceleration += this->accumulatedForce * (1/mass);
    this->velocity = this->velocity + (this->acceleration * time);
    this->velocity = this->velocity * powf(this->damping,time);
}

void P6Particle::Destroy()
{
    this->isDestroyed = true;
}

bool P6Particle::IsDestroyed()
{
    return this->isDestroyed;
}

void P6Particle::AddForce(VectorClass force)
{
    this->accumulatedForce += force;
}

//this is an impulse engine, forces are applied over a short period of time (per frame) then reset after
void P6Particle::ResetForce()
{
    this->accumulatedForce = VectorClass(0,0,0);
    this->acceleration = VectorClass(0,0,0);
}



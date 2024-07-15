#include "GravityForceGenerator.h"

using namespace P6;

GravityForceGenerator::GravityForceGenerator(const VectorClass gravity) : Gravity(gravity) {}

void GravityForceGenerator::UpdateForce(P6Particle* particle, float time)
{
    //Do nothing if mass is 0 below
    if (particle->mass <= 0) return;

    VectorClass force = Gravity * particle->mass;
    particle->AddForce(force);
}
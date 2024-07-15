#include "DragForceGenerator.h"

using namespace P6;

DragForceGenerator::DragForceGenerator() {}

DragForceGenerator::DragForceGenerator(float _k1, float _k2) : k1(_k1), k2(_k2) {}

void DragForceGenerator::UpdateForce(P6Particle* particle, float time)
{
    VectorClass force = VectorClass(0,0,0);

    //current velocity
    VectorClass currV = particle->velocity;

    //Get magnitude
    float mag = currV.findMagnitude(currV.x,currV.y);

    //if magnitude is <= 0, do nothing
    if (mag <= 0) return;

    float dragF = (k1 * mag) + (k2 * mag);
    //Get direction of velocity
    VectorClass dir = currV.findDirection(currV);

    //Apply force using to the opposite direction
    particle->AddForce(dir * -dragF);

}
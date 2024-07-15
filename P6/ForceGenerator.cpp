#include "ForceGenerator.h"

using namespace P6;

ForceGenerator::ForceGenerator() {}

void ForceGenerator::UpdateForce(P6Particle* p, float time)
{
    p->AddForce(VectorClass(0,0,0));
}
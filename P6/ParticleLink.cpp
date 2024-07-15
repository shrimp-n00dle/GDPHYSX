#include "ParticleLink.h"

using namespace P6;

float ParticleLink::CurrentLength()
{
    VectorClass ret = particles[0]->position - particles[1]->position;
    return ret.findMagnitude(ret.x,ret.y);
}
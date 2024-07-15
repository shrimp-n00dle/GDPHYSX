#pragma once
#include "P6Particle.h"

/*Base class that computes force needed to be applied to target particle*/
namespace P6
{
    class ForceGenerator
    {
        public:
        ForceGenerator();
        virtual void UpdateForce(P6Particle* p, float time);


    };
}
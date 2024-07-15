#pragma once
#include "ForceGenerator.h"

namespace P6
{
    //Froce generator that handles gravity
    class GravityForceGenerator : public ForceGenerator
    {
        private:
        //Acceleration due to gravity
        VectorClass Gravity = VectorClass(0,-9.8,0);

        public:
        //Constructor
        GravityForceGenerator(const VectorClass gravity);

        //Override update froce function of base class
        void UpdateForce(P6Particle* particle, float time) override;

    };
}

#pragma once
#include "ForceGenerator.h"

namespace P6
{
    class DragForceGenerator : public ForceGenerator
    {
        private:
        //First coefficent of friction
        float k1 = 0.74;
        //Second
        float k2 = 0.57;

        public:
        DragForceGenerator();
        DragForceGenerator(float _k1, float _k2);

        //Override of UpdateForce
        void UpdateForce(P6Particle* particle, float time) override;

    };
}
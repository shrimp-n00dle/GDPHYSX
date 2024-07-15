#pragma once
#include <list>
#include "P6Particle.h"
#include "ForceGenerator.h"

namespace P6
{
    class ForceRegistry
    {
        protected:
        /*Holds the references for the particle and generator pair, does not have any other use*/
        struct ParticleForceRegistry
        {
            P6Particle* particle;
            ForceGenerator* generator;
        };

        /*Lists pairs of the particles and tier generators*/
        std::list<ParticleForceRegistry> Registry;

        public:
        //Adds a apair to the list
        void Add(P6Particle* particle, ForceGenerator* generator);

        //Removes pair from list
        void Remove(P6Particle* particle, ForceGenerator* generator);

        //Clears the list of ALL pairs
        void Clear();

        //Calls update froce fh=unctions in ALL pairs
        void UpdateForces(float time);
        
    };
}
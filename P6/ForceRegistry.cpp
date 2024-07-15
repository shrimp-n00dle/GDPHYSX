#include "ForceRegistry.h"

using namespace P6;

void ForceRegistry::Add(P6Particle* particle, ForceGenerator* generator)
{
    //create a struct to be added
    ParticleForceRegistry toAdd;

    //Assign the pair
    toAdd.particle = particle;
    toAdd.generator = generator;

    //Add to list
    Registry.push_back(toAdd);
}

//Calls updateforce on all pairs
void ForceRegistry::UpdateForces(float time)
{
    //iterate through the list as sual
    for(std::list<ParticleForceRegistry>::iterator i = Registry.begin(); i != Registry.end(); i++)
    {
        //Call upate froce for the current pair
        i->generator->UpdateForce(i->particle, time);
    }
}

void ForceRegistry::Remove(P6Particle* particle, ForceGenerator* generator)
{
    Registry.remove_if([particle, generator] (ParticleForceRegistry reg)
    {
        return reg.particle == particle && reg.generator == generator;
    });
}

void ForceRegistry::Clear()
{
    Registry.clear();
}
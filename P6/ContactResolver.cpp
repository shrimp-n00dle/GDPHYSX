
#include "ContactResolver.h"

using namespace P6;

ContactResolver::ContactResolver(unsigned _maxIterations) : max_iterations(_maxIterations) {}

void ContactResolver::ResolveContacts(std::vector<P6::ParticleContact*> contacts, float time)
{

    current_iterations = 0;

    while(current_iterations < max_iterations)
    {
        unsigned current_index = 0;
        float curr_min = contacts[0]->GetSeparatingSpeed();
        float max_depth = contacts[0]->depth;

        for (int i = 1; i < contacts.size(); i++)
        {
            float ss = contacts[i]->GetSeparatingSpeed();

             if (ss < curr_min && (ss < 0 || 0 < contacts[i]->depth))
            {
                current_index = 1;
                curr_min = ss;

                 if (max_depth < contacts[i]->depth) max_depth = contacts[i]->depth;

            }

    }

        if (curr_min >= 0 && max_depth <= 0) return;
        

        contacts[current_index]->Resolve(time);
        current_iterations++;
    }
}
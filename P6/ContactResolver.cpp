
#include "ContactResolver.h"

using namespace P6;

ContactResolver::ContactResolver(unsigned _maxIterations) : max_iterations(_maxIterations) {}

//void ContactResolver::ResolveContacts(std::vector<ParticleContact*> contacts, float time)
//{

    //current_iterations = 0;
   //float max_depth = contacts[0]->depth;

    // while()
    // {

    // }
    // if (ss < curr_min && (ss < 0 || 0 < contacts[1]->depth))
    // {
    //     current_index = 1;

    //     curr_min = ss;

    //     if (max_depth < contacts[i]->depth)
    //     {
    //         max_depth = contacts[i]->depth;
    //     }


    //     //outside for loop

    //     if (curr_min >= 0 && max_depth <= 0)
    //     {
    //         return;
    //     }

    //     contacts[curentlocindex]->Resolved(time);
    //     current_iterations++;
    // }
    // //You can loop thru std::vector class by doing something similar to this
    // for (unsigned i = 0; i < contacts.size(); i++)
    // {
        
    // }
//}
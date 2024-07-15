#include "ParticleContact.h"

using namespace P6;

float ParticleContact::GetSeparatingSpeed()
{

    //Av
    VectorClass velocity = particles[0]->velocity;

    if(particles[1]) velocity -= particles[1]->velocity;

    //idk if correct
    return velocity.findDotProduct(velocity,contactNormal);
}

void ParticleContact::ResolveVelocity(float time)
{
    //sS
    float separatingSpeed = GetSeparatingSpeed();

    //if obj is already moving away from each other- skip
   if(separatingSpeed > 0) 
   {
    return;
   } 

   float newSS = -restitution * separatingSpeed;
   //mag of our delta velocity
   float deltaSpeed = newSS - separatingSpeed;

    //get total inverse mass of collsing particles
    //apply impulse based on this later
   float totalMass = (float)1/ particles[0]->mass;
   if (particles[1]) totalMass += (float)1 / particles[1]->mass;

   //Invalid collision if total mass is 0 or less
   if(totalMass <= 0) return;

   //mag of impuls eneeded to apply in collison
   float impulse_mag = deltaSpeed / totalMass;

   //get impulse vector using contact normal
   VectorClass Impulse = contactNormal * impulse_mag;

   //chang in V for Particle A
   VectorClass V_a = Impulse * ((float)1/ particles[0]->mass);
   particles[0]->velocity = particles[0]->velocity + V_a;

   if (particles[1])
   {
    //Apply impulse in the opposite direction for B
    VectorClass V_b = Impulse * ((float)-1 / particles[1]->mass);
    particles[1]->velocity = particles[1]->velocity + V_b;
   }
}

void ParticleContact::Resolve(float time){
    
    //v after coll
    ResolveVelocity(time);

    //pos after coll
    //Resolve interpenetration here order that matter much
    ResolveInterpenertration(time);

}


//add here first
void ParticleContact::ResolveInterpenertration(float time)
{
    //do nothing if depth is 0 or lower == barely touch
    if (depth <= 0) return;

    //total mass of collisions
    float totalMass = (float) 1 / particles[0]->mass;
    if(particles[1]) totalMass += (float)1 / particles[1]->mass;

//invalid collison if total mass is 0 or less
    if (totalMass <= 0 ) return;

    //higher mass == less likely for the particle to move
        //how much to move / how many units to move per total mass
    float totalMoveByMass = depth / totalMass;

    //directionf of the mmovement
    //how much to move and where // get vector of total movement involved
    VectorClass moveByMass = contactNormal * totalMoveByMass;

    //get the change in position for A
    VectorClass P_a = moveByMass * ((float) 1 / particles[0]->mass);
   
   //translate A
    particles[0]->position += P_a;

    if (particles[1])
    {
        //get the change in pos for B in the opp dir
        VectorClass P_b = moveByMass * (-(float) 1 / particles[1]->mass);
       //Translete for B
        particles[1]->position += P_b;
    }

    //restart, after solving - assume depth is now 0
    depth = 0;

}
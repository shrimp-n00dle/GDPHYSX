#include "AnchoredSpring.h"

using namespace P6;

AnchoredSpring::AnchoredSpring(VectorClass pos, float _springConst, float _restLen) : anchorPoint(pos), springConstant(_springConst), restLength(_restLen) {}


void AnchoredSpring::UpdateForce(P6Particle* particle, float time)
{
    //Get current position of particle
        VectorClass pos = particle->position;

        //Vector Pos->anchorpoint
        VectorClass force = pos - anchorPoint;

        //create magnitude of vector above
        float mag = force.findMagnitude(force.x,force.y);

        //
        float springForce = -springConstant * abs(mag - restLength);

        //get dir from the particle to anchor point
        //idk if correct
        force = force.findDirection(force);

        //apply force using direction above
        force = force * springForce;

        //add froce!
        particle->AddForce(force);
}

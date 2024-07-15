#pragma once
#include <list>
#include "P6Particle.h"
#include "ForceRegistry.h"
#include "GravityForceGenerator.h"
#include "ParticleContact.h"
#include "ParticleLink.h"

#include <vector>

namespace P6
{
    class PhysicsWorld
    {

        public:

        //contains the lsit of links
        std::list<ParticleLink*> Links;

        /*Create a Dynamic Array of contacts you can use
        the vector class for this*/
        std::vector<ParticleContact*> Contacts;


        ForceRegistry  forceRegistry;
        //The list of ALL our particles
        std::list<P6Particle*> Particles;

        PhysicsWorld();

        //Function to add the particles to the list
        void AddParticle(P6Particle* toAdd);
        //Universal update function to call the updates of ALL
        void Update(float time);

        //Function to easily add conacts
        void AddContact(P6Particle* p1, P6Particle* p2, float restitution, VectorClass contactNormal, float depth);

	    private:
		//Function that will check the list for any particles neededto be removed from simulation
		void UpdateParticleList();

        //Add gravity here feel free to adjust the value as needed
        GravityForceGenerator Gravity = GravityForceGenerator(VectorClass(0,-9.8,0));

        protected:
        //generates the contacs that needs to be resolved
        void GenerateContacts();
        
        //Set arbitrary default num for max number of resolve calls
        ContactResolver contactResolver = ContactResolver(20);

        //Get contacts that overlap
        void GetOverlaps();
    };
    
} // namespace name

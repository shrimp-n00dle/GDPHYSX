#include "PhysicsWorld.h"

using namespace P6;

PhysicsWorld::PhysicsWorld(){}

void PhysicsWorld::AddParticle(P6Particle* toAdd)
{
    //Adds a particle to the end of the list
    Particles.push_back(toAdd);

    //Automatically add particle and gravity generator to registry
    forceRegistry.Add(toAdd, &Gravity);
}

void PhysicsWorld::Update(float time)
{

    //Update the list before calling updates for particles
    UpdateParticleList();

    //Add gravity here, modify values if needed
    GravityForceGenerator Gravity = GravityForceGenerator(VectorClass(0,-9.8,0));

    /*call update forces before velocity and new positions of particle get calculated*/
    forceRegistry.UpdateForces(time);
    
    //Create an iterator that points at the start of the list
    for(std::list<P6Particle*>::iterator p = Particles.begin();
    
        //Continue looping until the end of the list
        p != Particles.end();

        //Move to the next particle
        p++)
    {
        (*p)->Update(time);
    }

    //call generate contacs here
    GenerateContacts();

    //Only Call Resolve Contactcs when there are contacts
    if (Contacts.size() > 0)
    {
        contactResolver.ResolveContacts(Contacts,true);
    }
}

void PhysicsWorld::UpdateParticleList()
{
    //Removes all particles in the list that returns true to the function below
    Particles.remove_if(
        //Checks all particles in the list
        //if their bool value is true
        [](P6Particle* p){ return p->IsDestroyed();}
    );
}

void PhysicsWorld::AddContact(P6Particle* p1, P6Particle* p2, float restitution, VectorClass contactNormal)
{

    //Create a Particle Contact
    ParticleContact *toAdd = new ParticleContact();

    //Assign the needed variables and values
    toAdd->particles[0] = p1;
    toAdd->particles[1] = p2;
    toAdd->restitution = restitution;
    toAdd->contactNormal = contactNormal;

    //Similar to a list you can just call push_back
    Contacts.push_back(toAdd);
}

void PhysicsWorld::GenerateContacts()
{
    //clear the current list of contatcs
    Contacts.clear();

    //iterate through the list of links
    for (std::list<ParticleLink*>::iterator i = Links.begin();
        i != Links.end(); i++)
        {
            //try and get the contact for the link
            ParticleContact* contact = (*i)->GetContact();

            //if contacts exists- push it to the list
            if (contact != nullptr)
            {
                Contacts.push_back(contact);
            }
        }
}
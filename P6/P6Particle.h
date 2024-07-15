#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VectorClass.h"

//1 unit = 1m
//1m = 1 px

namespace P6
{
	class P6Particle
	{

	public:
		/*How much velocity is left per update*
		0.9f by default to simulate all the different type of drag a particle may experience. You can modify it to your liking.*/
		float damping = 0.9f;
		VectorClass position, velocity, acceleration;
		float mass = 0;

		//size of particle
		float radius = 1.0f;

		//how bouncy the particle is
		float restitution = 1.0f;
		
	protected:
		/*force accumulated by the particle the entire time*/
		VectorClass accumulatedForce = VectorClass(0,0,0);
		bool isDestroyed = false;


	public:
		P6Particle();
		P6Particle(VectorClass position, VectorClass velocity, VectorClass acceleration);

	protected:
		//Update particle position relative to time
		void UpdatePosition(float time);
		
		//Update particle velocity relative to time
		void UpdateVelocity(float time);

	public:
		//Updates particle using given time
		void Update(float time);

        //Will set our flag
		void Destroy();

		//Getter for the IsDestroyed variable
		bool IsDestroyed();

		//Add force to teh particle
		void AddForce(VectorClass force);

		//Reset accumulated force and acceleration per frame
		void ResetForce();


	};
}



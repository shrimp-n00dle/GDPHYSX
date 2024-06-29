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
		VectorClass position, velocity, acceleration;
		float mass = 0;

	public:
		P6Particle();
		P6Particle(VectorClass position, VectorClass velocity, VectorClass acceleration);

	protected:
		//Update particle position relative to time
		void updatePosition(float time);
		
		//Update particle velocity relative to time
		void updateVelocity(float time);

	public:
		//Updates particle using given time
		void Update(float time);

	};
}



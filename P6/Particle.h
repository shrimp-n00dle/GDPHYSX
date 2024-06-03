#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MyVector.h"

//1 unit = 1m
//1m = 1 px

namespace P6
{
	class P6Particle
	{
	public:
		MyVector position, velocity, acceleration;//glm::vec3 position;
		float mass = 0;
		//glm::vec3 velocity, acceleration;

	public:
		P6Particle();

	protected:
		void updatePosition(float time)
		{
			this->position = this->position + (this->velocity * time) + ((this->acceleration * time * time) * (1.0f / 2.0f));
		}
		void updateVelocity(float time) {}

	public:
		void Update(float time)
		{
			this->updatePosition(time);
			updateVelocity(time);
		}

	};
}



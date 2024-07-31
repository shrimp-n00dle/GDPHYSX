// #pragma once

// #pragma once

// #include <vector>
// #include <iostream>

// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

// #include "../tiny_obj_loader.h"

// #include "P6Particle.h"
// #include "VectorClass.h"

// namespace Model
// {
//     using namespace P6;
//     class RenderParticle
//     {
//         public:
//         //Reference for our P6 Particle
//         P6::P6Particle* PhysicsParticle;
//         P6::VectorClass Position;

//         //Reference for our 3D Model
//         OpenGLObject* RenderObject;

//         //Color
//         P6::VectorClass Color;

//         //default constructor with white particle
//         RenderParticle(P6::P6Particle* p, OpenGLObject* obj);

//         //Constructor in case we want to define color
//         RenderParticle(P6::P6Particle* p, OpenGLObject* obj, P6::VectorClass c, VectorClass position);

//         void Draw();
//     };
// }


#pragma once

#include "P6Particle.h"
#include "../Model/Model3D.h"

namespace P6 {
	using namespace model;

	class RenderParticle
	{
		//FIELDS
		public:
			P6Particle* physicsParticle;
			Model3D* renderObject;
		
		//CONSTRUCTOR
		public:
			RenderParticle(P6Particle* p, Model3D* model);

		//METHODS
			void draw();
	};

}


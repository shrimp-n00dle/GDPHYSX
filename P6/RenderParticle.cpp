// #include "RenderParticle.h"

// using namespace P6;


// RenderParticle::RenderParticle(P6::P6Particle* p, OpenGLObject* obj) : PhysicsParticle(p),  RenderObject(obj)
// {
//     Color = P6::VectorClass(1,1,1);
// }


// RenderParticle::RenderParticle(P6::P6Particle* p, OpenGLObject* obj, P6::VectorClass c) : PhysicsParticle(p),  RenderObject(obj)
// {}

// void RenderParticle::Draw()
// {
//     //Check if particle is not yet destroyed
//     if (!PhysicsPartcle->IsDestroyed())
//     {
//         //set color
//         RenderObject->Color = (glm::vec3)Color;
//         //set position
//         RenderObject->Position = (glm::vec3)Physics;
//         //Draw!
//         RenderObject->Draw();
//     }
// }


#include "RenderParticle.h"
using namespace P6; 

//constructor
RenderParticle::RenderParticle(P6Particle* p, Model3D* model) {
	this->physicsParticle = p;
	this->renderObject = model;
}

// this function is used for updating the position of the model based on the position 
// of the particle, also used for calling the renderer of the object
void RenderParticle::draw() {
	if (!this->physicsParticle->IsDestroyed()) {
		this->renderObject->setPosition(this->physicsParticle->position);
		this->renderObject->drawModel();
	}
}
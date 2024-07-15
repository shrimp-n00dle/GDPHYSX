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
// #pragma once

// #include "P6Particle.h"
// #include "VectorClass.h"

// namespace P6
// {
//     class RenderParticle
//     {
//         public:
//         //Reference for our P6 Particle
//         P6::P6Particle* PhysicsParticle;

//         //Reference for our 3D Model
//         OpenGLObject* RenderObject;

//         //Color
//         P6::VectorClass Color;

//         //default constructor with white particle
//         RenderParticle(P6::P6Particle* p, OpenGLObject* obj);

//         //Constructor in case we want to define color
//         RenderParticle(P6::P6Particle* p, OpenGLObject* obj, P6::VectorClass c);

//         void Draw();
//     };
// }
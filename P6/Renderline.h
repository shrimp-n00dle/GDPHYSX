#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VectorClass.h"

class Renderline
{
    public:
    P6::VectorClass P1,P2;
    glm::mat4 ProjectionMatrix;

    P6::VectorClass Color;

    Renderline(P6::VectorClass p1, P6::VectorClass p2, P6::VectorClass color);

    void Update(P6::VectorClass p1, P6::VectorClass p2, glm::mat4 projectionMatrix);

    void Draw();


};
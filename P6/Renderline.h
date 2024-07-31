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

    glm::vec4 Color;

    Renderline(P6::VectorClass p1, P6::VectorClass p2, glm::vec4 color);

    void Update(P6::VectorClass p1, P6::VectorClass p2, glm::mat4 projectionMatrix);

    void Draw();


};
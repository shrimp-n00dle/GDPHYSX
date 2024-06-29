#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace P6 {
    class VectorClass
    {
    private:
        float x,y,z;
        float velocity,force;
        glm::vec3 position;
        float magnitude = 1.0f;
    public:
        VectorClass(float x, float y, float z);
        VectorClass();

        explicit operator glm::vec3() const { return glm::vec3(x, y, z); }

        /*basic operators*/

        //addition
        VectorClass operator+ (const VectorClass vector);

        //subtraction
        VectorClass operator- (const VectorClass vector);

        //basic multipilcation
        VectorClass operator* (const VectorClass vector);
        VectorClass operator* (float value);

        //scalar multipilcation
        VectorClass scalarMultiplication (const VectorClass vector, float value);




        /*Magnitude and Direction*/

        //magnitude
        float findMagnitude(float x, float y);

        //direction
        VectorClass findDirection(const VectorClass vector);

        /*Vector Products*/

        //component

        //scalar

        //vector
    };
}
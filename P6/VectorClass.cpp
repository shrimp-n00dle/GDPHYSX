#include "VectorClass.h"

using namespace P6;

VectorClass::VectorClass(){}

VectorClass::VectorClass(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

VectorClass VectorClass::operator+ (const VectorClass vector)
{
    return VectorClass (this->x + vector.x,this->y + vector.y,this->z + vector.z);
}

VectorClass VectorClass::operator+= (const VectorClass vector)
{
    return VectorClass (this->x += vector.x,this->y += vector.y,this->z += vector.z);
}

VectorClass VectorClass::operator- (const VectorClass vector)
{
    return VectorClass (this->x - vector.x,this->y - vector.y,this->z - vector.z);
}

VectorClass VectorClass::operator-= (const VectorClass vector)
{
    return VectorClass (this->x -= vector.x,this->y -= vector.y,this->z -= vector.z);
}

VectorClass VectorClass::operator* (const VectorClass vector)
{
    return VectorClass (this->x * vector.x,this->y * vector.y,this->z * vector.z);
}

// VectorClass VectorClass::scalarMultiplication (const VectorClass vector, float value)
// {
//     this->x = vector.x * value;
//     this->y = vector.y * value;
//     this->z = vector.z * value;

//     return VectorClass(this->x,this->y,this->z);
// }

VectorClass VectorClass::operator* (float value)
{
    this->x = this->x * value;
    this->y = this->y * value;
    this->z = this->z * value;

    return VectorClass(this->x,this->y,this->z);
}

float VectorClass::findMagnitude(float x, float y)
{
    this->magnitude = sqrt((x * x) + (y * y));
    return this->magnitude;
}

float VectorClass::findSqMagnitude(float x, float y)
{
     this->magnitude = (x * x) + (y * y);
    return this->magnitude;
}

VectorClass VectorClass::findDirection(const VectorClass vector)
{
    this->x = vector.x / this->magnitude;
    this->y = vector.y / this->magnitude;
    this->z = vector.z / this->magnitude;

    return VectorClass(this->x,this->y,this->z);
}

float VectorClass::findDotProduct(const VectorClass vector, const VectorClass vector2)
{
    this->dot = (vector.x * vector2.x) + (vector.y * vector2.y) + (vector.z * vector2.z);
    return this->dot;
}

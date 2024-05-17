#include "MyVector.h"

using namespace Physics;


MyVector::MyVector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//Magnitude
void MyVector::findMagnitude(float _x, float _y, float _z)
{
	this->magnitude = sqrt((_x * _x) + (_y * _y) + (_z * _z));
}

//Direction
void MyVector::findDirection(float magnitude, MyVector vector1)
{
	this->direction = glm::vec3(vector1.x / magnitude, vector1.y / magnitude, vector1.z / magnitude);
}

//Basic Operations
void MyVector::Add(MyVector vector)
{
	vector.x = vector.x + this->x;
	vector.y = vector.y + this->y;
	vector.z = vector.z + this->z;
}
void MyVector::Subtract(MyVector vector)
{
	vector.x = vector.x - this->x;
	vector.y = vector.y - this->y;
	vector.z = vector.z - this->z;
}
void MyVector::Multiplication_scalar(MyVector vector, float scalarValue)
{
	vector.x = vector.x + scalarValue;
	vector.y = vector.y + scalarValue;
	vector.z = vector.z + scalarValue;
}

//Vector Products
void MyVector::findComponentProduct(MyVector vector1, MyVector vector2)
{
	this->x = vector1.x * vector2.x;

	this->y = vector1.y * vector2.y;

	this->z = vector1.z * vector2.z;
}
void  MyVector::findScalarProduct(MyVector vector1, MyVector vector2)
{
	findComponentProduct(vector1, vector2);
	this->dot = this->x + this->y + this->z;
}

void  MyVector::findVectorProduct(MyVector vector1, MyVector vector2)
{
	this->x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
	this->y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
	this->z = (vector1.x * vector2.y) - (vector1.y * vector2.x);
}
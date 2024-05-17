#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace Physics {

	class MyVector
	{
	public:
		float x, y, z;

		float magnitude = 0.0f, dot = 0.0f;
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

		//from zoom session
		explicit operator glm::vec3() const { return glm::vec3(x, y, z); }

		MyVector(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		//Magnitude
		void findMagnitude(float _x, float _y, float _z)
		{
			this->magnitude = sqrt((_x * _x) + (_y * _y) + (_z * _z));
		}

		//Direction
		void findDirection(float magnitude, MyVector vector1) 
		{
			this->direction = glm::vec3(vector1.x / magnitude, vector1.y / magnitude, vector1.z / magnitude);
		}

		//Basic Operations
		void Add(MyVector vector) 
		{
			vector.x = vector.x + this->x;
			vector.y = vector.y + this->y;
			vector.z = vector.z + this->z;
		}
		void Subtract(MyVector vector)
		{
			vector.x = vector.x - this->x;
			vector.y = vector.y - this->y;
			vector.z = vector.z - this->z;
		}
		void Multiplication_scalar(MyVector vector, float scalarValue)
		{
			vector.x = vector.x + scalarValue;
			vector.y = vector.y + scalarValue;
			vector.z = vector.z + scalarValue;
		}

		//Vector Products
		void findComponentProduct(MyVector vector1, MyVector vector2)
		{
			this->x = vector1.x * vector2.x;

			this->y = vector1.y * vector2.y;

			this->z = vector1.z * vector2.z;
		}
		void findScalarProduct(MyVector vector1, MyVector vector2)
		{ 
			findComponentProduct(vector1,vector2);
			this->dot = this->x + this->y + this->z;
		}

		void findVectorProduct(MyVector vector1, MyVector vector2)
		{
			this->x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
			this->y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
			this->z = (vector1.x * vector2.y) - (vector1.y * vector2.x);
		}

		/*
		MyVector() : x(0), y(0), z(0)
		{}

		MyVector(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z)
		{}

		explicit operator glm::vec3() const { return glm::vec3(x, y, z); }

		MyVector operator+ (const MyVector v)
		{
			return MyVector(this->x + v.x, this->y + v.y, this->z + v.z);
		}

		//if +=
		void operator += (const MyVector v)
		{
			this->x += this->x + v.x;
			this->y += this->y + v.y;
			this->z += this->z + v.z;

		}

		MyVector Add(MyVector b)
		{
			return MyVector(this->x + b.x, this->y + b.y, this->z + b.z);
		}
		*/

	};

}



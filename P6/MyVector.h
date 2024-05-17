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

		MyVector(float x, float y, float z){}

		//Magnitude
		void findMagnitude(float _x, float _y, float _z){}

		//Direction
		void findDirection(float magnitude, MyVector vector1) {}

		//Basic Operations
		void Add(MyVector vector) {}
		void Subtract(MyVector vector){}
		void Multiplication_scalar(MyVector vector, float scalarValue) {}

		//Vector Products
		void findComponentProduct(MyVector vector1, MyVector vector2){}
		void findScalarProduct(MyVector vector1, MyVector vector2)
		{}

		void findVectorProduct(MyVector vector1, MyVector vector2)
		{}

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



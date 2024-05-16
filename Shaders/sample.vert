#version 330 core

//Gets the data at Attrib Index 0
//Converts and stores it into a Vec3
layout(location = 0) in vec3 aPos;

//Creates a Transform variable
//We'll assign the transformation matrix here later
uniform mat4 transform;

uniform mat4 transform2;

//Projection Matrix (dito lalagay)
uniform mat4 projection;

void main()
{
	//Multiply the tranformation matrix to the 
	//vec4 version of aPos to get the final position 
	
	//vec3 aPos = vec3(aPos.x + x, aPos.y, aPos.z);
	//gl_Position = transform * vec4(aPos, 1.0);
	gl_Position = projection * //Multiply the Projection Matrix with the transform
					transform * //Multiply the matrix with the position
						vec4(aPos, 1.0); //Turns our 3x1 matrix into a 4x1
}
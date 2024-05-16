#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <vector>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float x = 0.f,y = 0.f ,z = 0.f;
glm::mat4 identity_matrix = glm::mat4(1.0f);


float scale_x = 0.5f;
float scale_y = 0.5f;
float scale_z = 1.0f;

float theta = 0.0f;

float axis_x = 0.f;
float axis_y = 1.0f;
float axis_z = 0.f;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    float window_width = 600.f;
    float window_height = 600.f;
    /*
    //Create a 3x3 indentity matrix
    glm::mat3 identity_matrix3 = glm::mat3(1.0f);
    //Create a 4x4 indentity matrix
    glm::mat4 identity_matrix4 = glm::mat4(1.0f);

    //3D Translation Matrix
    glm::mat4 translation =
        glm::translate(identity_matrix4, glm::vec3(x, y, z));

    //3D Scale Matrix
    glm::mat4 scale =
        glm::scale(identity_matrix4, glm::vec3(x, y, z));

    //3D Rotation Matrix
    glm::mat4 rotation =
        glm::rotate(identity_matrix4, glm::radians(theta), glm::vec3(x, y, z));
        */

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(window_width, window_height, "Jan Elizabeth Vingno", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

 


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //call this to initialize OpenGL() calls for later
    gladLoadGL();

    //min x min y width height
    //helps with split screen
    glViewport(0,0,600,600);


    //After gladLoadGL() 
    //Load shader
    std::fstream vertSrc("Shaders/sample.vert");
    std::stringstream vertBuff;
    //Add file stream to string stream
    vertBuff << vertSrc.rdbuf();

    //Convert stream to chac array
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    //Fragment Shader
    //Load shader
    std::fstream fragSrc("Shaders/sample.frag");
    std::stringstream fragBuff;
    //Add file stream to string stream
    fragBuff << fragSrc.rdbuf();

    //Convert stream to chac array
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    //Vertex Shader creation
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Assign source code to Vertex Shader
    glShaderSource(vertexShader,1,&v, NULL);
    //Compile Vertex Shader
    glCompileShader(vertexShader);

    //Frag Shader creation
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Assign source code to Vertex Shader
    glShaderSource(fragShader, 1, &f, NULL);
    //Compile Vertex Shader
    glCompileShader(fragShader);

    //Compile Shader Program
    GLuint shaderProg = glCreateProgram();
    //Attach compiled Vertex Shader
    glAttachShader(shaderProg, vertexShader);
    //Attach compiled Fragment Shader
    glAttachShader(shaderProg,fragShader);

    //Finalize compilation process
    glLinkProgram(shaderProg);

    //relative path to the mesh
    std::string path = "3D/sphere.obj";

    //Will contain the mesh's shapes
    std::vector<tinyobj::shape_t> shapes;

    //Will contain the mesh's material
    std::vector<tinyobj::material_t> material;

    //Some error messages might popup
    std::string warning, error;

    //Basic Attributes related to the mesh
    tinyobj::attrib_t attributes;

    //assuming it was successful
    std::vector<GLuint> mesh_indices;

    if (tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error, path.c_str()))
    {
        for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
            mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
        }
    }
    else {
        std::cout << "Model failed to load" << std::endl;
    }

 
    //definition of the 3d model
    GLfloat vertices[]{
        //x1  //y1 //z1
         0.0f,0.5f,0.0f,
        //x2  //y2 //z2
       -0.5f,-0.5f,0.0f,
        //x3  //y3 //z3
        0.5f,-0.5f,0.0f,
    };

    //Element Buffer Object  EBO Index Array
    //EBO is a VBO that stores index data
    GLuint indices[]{
        0,1,2 //triangle A
        //1,2,3 //triangle B 
    };

    //Create VAO/VBO Variables
    GLuint VAO, VBO, EBO;
    //Initialize the VAO,VBO and EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    //Currently editing VAO = null
    glBindVertexArray(VAO);
    //Currently editing VAO = VAO of glBindVertexArray

    //Currently editing VBO = null
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //this method assigns VAO = VBO if its currently editing and currerntly editing vbo = vbo
    //Currently editing VBO = VBO of glBindBuffer

    //VAO <- VBO, meaning VAO will store ano yung value ng VBO parameter 

    glBufferData(GL_ARRAY_BUFFER,
        //  sizeof(vertices), //bytes
        sizeof(GL_FLOAT) * attributes.vertices.size(), //bytes
        //vertices, //array
        //&attributes.vertices[0], //array
        attributes.vertices.data(),
        GL_STATIC_DRAW); //for optimazation purposes

    glVertexAttribPointer(
        0, //0 pos, 1 tex, 2 norms
        3, // x y z
        GL_FLOAT, //type of array to expect
        GL_FALSE, //is this normalize? false for now
        3 * sizeof(float),
        (void*)0
    );

    //Current Status VAO <- VBO

    //this method SHOULD be in between glVertexAttribPointer and glEnableVertexAttribArray
    //Currently editing VBO = VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //Currently editing VBO = EBO

    //Current Status VAO <- VBO
    //                   <- EBO

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        // sizeof(indices),
        sizeof(GLuint) * mesh_indices.size(),
        // indices,
         //or &mesh_indices[0]
        mesh_indices.data(),
        GL_STATIC_DRAW);
    //parameters: what GL buffer?, size of indiced, the indices mismo and static or dynamic draw?

    glEnableVertexAttribArray(0);

    //Currently editing VBO = VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Currently editing VBO = null

    //Currently editing VAO = VAO
    glBindVertexArray(0);
    //Currently editing VAO = null

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glm::mat4 projection_matrix = glm::ortho(
    -2.f, //left
    2.f, //right
    -2.f, //bottom
    2.f,//top
    -1.f, //znear
    1.f //zfar
    );

    //if z is 0, wala ang obj


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

       // theta += 0.050f;
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //Get the variable named transform _matrix
        glm::mat4 identity_matrix = glm::mat4(1.0f);
        

        //Start with the translation matrix
        glm::mat4 transformation_matrix = glm::translate(identity_matrix,
                                          glm::vec3(x, y, z));
  
        //Multiply the resulting matrix with the scale matrix
        transformation_matrix = glm::scale(transformation_matrix, glm::vec3(scale_x, scale_y, scale_z));

        //Multiply it with rotation matrix
        transformation_matrix = glm::rotate(transformation_matrix,
                                glm::radians(theta),
                                glm::normalize(glm::vec3(axis_x, axis_y, axis_z)));


        //Setting the projection 
        unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));


        //Setting the transformation
        //get the location of the transform variable in the shader
        unsigned int transformLoc = glGetUniformLocation(shaderProg, "transform");
        //assign the matrix
        glUniformMatrix4fv(transformLoc, //address of the transform variable
                            1, //how many matrices to assign
                            GL_FALSE, //transpose?
                            glm::value_ptr(transformation_matrix)); //pointer to the matrix

        //Tell openGl to use this shader
        //for the VAO/s below
        glUseProgram(shaderProg);
        glBindVertexArray(VAO);

        //you can render triangles using VAOs
        //glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES,0,3); 
        //with EBOs, you can call the foolowing method instead:
        glDrawElements(GL_TRIANGLES, /*sizeof(indices)*/ GLsizei(mesh_indices.size()), /*type of array is: */ GL_UNSIGNED_INT, /*starting at index 0*/0);
        //what type of primitive, starting atindex 0 and 3 points

        /* Swap front and back buffers */
        glfwSwapBuffers(window);


        /* Poll for and process events */
        glfwPollEvents();
    }

    //Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

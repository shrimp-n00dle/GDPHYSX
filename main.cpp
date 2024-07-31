#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <vector>
#include <string>

#include "Model/Model3D.h"
#include "Model/Shader.h"
#include "Model/ModelManager.h"

#include "P6/Springs/AnchoredSpring.h"
#include "P6/Springs/ParticleSpring.h"

#include "P6/ContactResolver.h"

#include "P6/DragForceGenerator.h"
#include "P6/ForceGenerator.h"
#include "P6/ForceRegistry.h"
#include "P6/GravityForceGenerator.h"

#include "P6/P6Particle.h"
#include "P6/ParticleContact.h"
#include "P6/ParticleLink.h"
#include "P6/PhysicsWorld.h"

#include "P6/Renderline.h"
#include "P6/RenderParticle.h"
#include "P6/Rod.h"
#include "P6/VectorClass.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

//TO DO : Also put the needed shaders and fragments in individual classes AND Review GRAP AGAIN
using namespace std::chrono_literals;
//our time inbetween frames// 16ms for  1/60
constexpr std::chrono::nanoseconds timestep(16ms);

float x = 0.f,y = 0.f ,z = 0.f;
glm::mat4 identity_matrix = glm::mat4(1.0f);

using namespace model;

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

    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);

    //Create an instance of our physics world
    P6::PhysicsWorld pWorld = P6::PhysicsWorld();
    ModelManager modelManager = ModelManager();
    P6::P6Particle* particle = new P6::P6Particle();
    P6::P6Particle* particle2 = new P6::P6Particle();
    std::list<P6::RenderParticle*> RenderParticles;
    P6::DragForceGenerator drag = P6::DragForceGenerator(0.14,0.1);
    pWorld.forceRegistry.Add(particle, &drag);
    //particle.position = P6::VectorClass(150,0,0);
    particle->position = P6::VectorClass(-10,0,0);
    //In KG
    particle->mass = 1;
    //Around (0,6000,0) KG m / s^2
    particle->AddForce(P6::VectorClass(0,6000,0));
    //this is 100m/s to the right
    particle->velocity = P6::VectorClass(100, 0, 0);
    //Acceleration is -30 m/s2 to the left
    particle->acceleration = P6::VectorClass(-30, 0, 0);
    pWorld.AddParticle(particle);

    //particle2->position = P6::VectorClass(50,0,0);
    particle2->position = P6::VectorClass(0,3,0);
    particle2->mass = 5;
    particle2->AddForce(P6::VectorClass(0,6000,0));
    //this is 100m/s to the right
    particle2->velocity = P6::VectorClass(50, 0, 0);
    //Acceleration is -30 m/s2 to the left
    particle2->acceleration = P6::VectorClass(-30, 0, 0);
    pWorld.AddParticle(particle2);

    particle->AddForce(P6::VectorClass(0.0,1.0f,0.0f) * 500000);

    P6::Rod* r = new P6::Rod();
    r->particles[0] = particle;
    r->particles[1] = particle2;
    r->length = 200;

    pWorld.Links.push_back(r);

    P6::ParticleSpring pS = P6::ParticleSpring(particle,5,1);
    pWorld.forceRegistry.Add(particle2,&pS);

    P6::ParticleSpring pS2 = P6::ParticleSpring(particle2,5,1);
    pWorld.forceRegistry.Add(particle,&pS2);

    //turn off gravity for now
    P6::GravityForceGenerator Gravity = P6::GravityForceGenerator(P6::VectorClass(0,0,0));

    //Manually create  objs with ff paramters
    P6::ParticleContact contact = P6::ParticleContact();
    contact.particles[0] = particle;
   contact.particles[1] = particle2;

    contact.contactNormal = particle->position - particle2->position;
    contact.contactNormal = contact.contactNormal.findDirection(contact.contactNormal);
    contact.restitution = 1;

    particle->velocity = P6::VectorClass(-30,0,0);
    particle2->velocity = P6::VectorClass(30,0,0);

    P6::VectorClass dir = particle->position - particle2->position;
    dir.findDirection(dir);

    //You can now add contatcs similar to the one below
   pWorld.AddContact(particle, particle2, 1, dir, 0);

    //Create spring anchored to  20,0 of the physics world
    //with a constant of 5 and rest length of 0.5m
    P6::AnchoredSpring aSpring = P6::AnchoredSpring(P6::VectorClass(20,0,0),5,0.5);
    //Connect the spring to a particle and
    pWorld.forceRegistry.Add(particle2,&aSpring);

    //Renderline line here

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
    -100.f, //left
    100.f, //right
    -100.f, //bottom
    100.f,//top
    -1.0f, //znear
    1000.f //zfar
    );
    //if z is 0, wala ang obj

    Model3D* model = new Model3D(glm::vec3(1.0, 1.0, 1.0), glm::vec4(1, 1, 1, 1), shaderProg);
    model->loadModel("3D/sphere.obj", &VBO);
    //model->setCameraProperties(projection, viewMatrix);
    modelManager.AddModel(model);
    model->setCameraProperties(projection_matrix, identity_matrix);

        Model3D* model2 = new Model3D(glm::vec3(1.0, 1.0, 1.0), glm::vec4(1, 1, 1, 1), shaderProg);
    model->loadModel("3D/sphere.obj", &VBO);
    //model->setCameraProperties(projection, viewMatrix);
    modelManager.AddModel(model);
    model->setCameraProperties(projection_matrix, identity_matrix);

      //INSTANTIATE RENDER_PARTICLE
    RenderParticle* rp = new RenderParticle(particle, model);
    RenderParticles.push_back(rp);

      //INSTANTIATE RENDER_PARTICLE
    RenderParticle* rp2 = new RenderParticle(particle2, model2);
    RenderParticles.push_back(rp2);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        //current time
        curr_time = clock::now();

        //check duration ibetween the last iteration
        auto dur = std::chrono::duration_cast< std::chrono::nanoseconds> (curr_time - prev_time);

        //set prev with current for the next iteration
        prev_time = curr_time;

        //add duartion since last iteration
        //to the time since our last "frame"
        curr_ns += dur;

        if (curr_ns >= timestep)
        {
            //convert ns to ms
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);

            std::cout << "MS: " << (float)ms.count() << "\n";
            curr_ns -= timestep;

            //Reset
            curr_ns -= curr_ns;

            //more updates here later
            std::cout << "P6 Update" << std::endl;

            //Update of physics world
            pWorld.Update((float)ms.count() / 1000);
            //testing contact resolver here
            contact.Resolve((float)ms.count() / 1000);

        }
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //Get the variable named transform _matrix
        glm::mat4 identity_matrix = glm::mat4(1.0f);
        

        //Start with the translation matrix
        glm::mat4 transformation_matrix = glm::translate(identity_matrix,
                                          glm::vec3(0,0,0));
  
        //Multiply the resulting matrix with the scale matrix
        transformation_matrix = glm::scale(transformation_matrix, glm::vec3(1, 1, 1));

        //Multiply it with rotation matrix
        transformation_matrix = glm::rotate(transformation_matrix,
                                glm::radians(theta),
                                glm::normalize(glm::vec3(0,1,0)));


        //Setting the projection 
        unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));


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

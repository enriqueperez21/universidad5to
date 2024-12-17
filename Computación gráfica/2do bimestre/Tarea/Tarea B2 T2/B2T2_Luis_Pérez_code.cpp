#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_s.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION //Add to use stb_image.h
#include "learnopengl/stb_image.h" //Add to use stb_image.h

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Luis Perez 0705052728", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("shaders/B2_T2_Luis_Perez.vs", "shaders/B2_T2_Luis_Perez.fs"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords (note that we changed them to 'zoom in' on our texture image)
         -0.4f, 0.0f, 0.0f,     1.0f, 0.0f, 0.0f,   0.3f, 0.0f,//v0
         0.0f, 0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   0.0f, 0.5f,//v1
         0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f,   0.7f, 0.0f,//v2
        -0.15f,0.65f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.9f,//v3
        0.15f,0.65f, 0.0f,      1.0f, 0.0f, 0.0f,   0.6f, 0.2f,//v4
        0.0f, 0.5f,  0.0f,      0.0f, 1.0f, 0.0f,   0.8f, 0.1f,//v5
         -0.3f,0.65f, 0.0f,     0.0f, 1.0f, 0.0f,   0.4f, 0.1f,//v6
         0.3f,0.65f, 0.0f,      0.0f, 0.0f, 1.0f,   0.7f, 0.2f,//v7
         0.0f, 0.9f, 0.0f,      0.0f, 0.0f, 1.0f,   0.3f, 0.9f,//v8
        -0.45f,0.0f, 0.0f,      1.0f, 0.0f, 0.0f,   0.0f, 0.0f,//v9
        -0.25f,0.0f, 0.0f,      0.0f, 0.0f, 1.0f,   0.0f, 0.0f,//v10
        -0.25f,-0.3f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f,//v11
        -0.05f,-0.3f, 0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,//v12
         0.2f,  0.0f, 0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,//v13
        -0.05f,-0.5f, 0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,//v14
        -0.25f,-0.5f, 0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,//v15
        -0.1f, -0.5f, 0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,//v16
        -0.1f, -0.7f, 0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,//v17
        -0.3f, -0.7f, 0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f//v18
    };
    unsigned int indices[] = {
        //Top part
        3, 4, 1, //TopTriangle1
        6, 7, 8, //TopTriangle2 
        0, 1, 2, //CenterTriangle - Amarillo

        //Low part
        9, 10, 11, //parallelogram1/2
        10, 11, 12, //parallelogram2/2
        10, 12, 13, //FirstLowTriangle
        11, 12, 14, //LowSquared1/2
        11, 14, 15, //LowSquared2/2
        16, 17, 18 //LastLowTriangle
    };

    unsigned int VBO, VAO, EBO; //
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO); // 

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Para EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //VERTEX ATTRIBUTE POINTER
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture attribute ***************************
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    //Cargar la textura 1***************************
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("textures/textura1.jpg", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //Cargar la textura 2***************************

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    data = stbi_load("textures/textura2.jpg", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // render loop
    // -----------

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //*********************
        float timeValue = glfwGetTime();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(ourShader.ID, "useTexture"), true);
        glUniform1f(glGetUniformLocation(ourShader.ID, "visibility"), 1.0f);

        //Tarea
         // create transformations
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.5f * (sin(glfwGetTime())), 0.5f, 0.5f));//se traslada en el eje x en el tiempo
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));//respecto al eje x  y "y"
        transform = glm::scale(transform, glm::vec3(0.7, 0.7, 0.7)); //factor de escala

        // get matrix's uniform location and set matrix
        ourShader.use();
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        //**********************

        // render the triangle
        ourShader.use();

        //proceso normal
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

        //*****
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(ourShader.ID, "useTexture"), true);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(15 * sizeof(unsigned int)));

        // Render second instance of the figure
        glm::mat4 transform2 = glm::mat4(1.0f);
        transform2 = glm::translate(transform, glm::vec3(0.3f * (sin(glfwGetTime())), 0.5f, 0.5f));//se traslada en el eje x en el tiempo
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform2));

        glBindTexture(GL_TEXTURE_2D, texture2); // Usar textura 2
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);


        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 

}
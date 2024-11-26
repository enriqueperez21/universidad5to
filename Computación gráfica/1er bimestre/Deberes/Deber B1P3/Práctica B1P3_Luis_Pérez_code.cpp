#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/shader_s.h>

#include <iostream>

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CG Exercise 7 Part 3", NULL, NULL);
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
    Shader ourShader("shaders/shader_B1P3.vs", "shaders/shader_B1P3.fs"); // you can name your shader files however you like

    //Create a new variable with the amount of triangles
    const int trianglesAmount = 9;

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // colors
         //CenterTriangle - Amarillo
         -0.4f, 0.0f, 0.0f, 0.9922f, 0.8078f, 0.0039f,//v1
         0.0f, 0.5f, 0.0f,  0.9922f, 0.8078f, 0.0039f,//v2
         0.0f, 0.0f, 0.0f,  0.9922f, 0.8078f, 0.0039f,//center
         //TopTriangle1 - Naranja
         -0.15f,0.65f, 0.0f, 0.9922f, 0.6078f, 0.2157f,//v1
         0.15f,0.65f, 0.0f,  0.9922f, 0.6078f, 0.2157f,//v2
         0.0f, 0.5f,  0.0f,  0.9922f, 0.6078f, 0.2157f,//v3
         //TopTriangle2 - Verde
         -0.3f,0.65f, 0.0f, 0.1882f, 0.8f, 0.5f,//v1
         0.3f,0.65f, 0.0f,  0.1882f, 0.8f, 0.5f,//v2
         0.0f, 0.9f, 0.0f,  0.1882f, 0.8f, 0.5f,//v3
         //parallelogram1/2 - Morado
         -0.45f,0.0f, 0.0f,  0.3922f, 0.4f, 0.8f,//v1
         -0.25f,0.0f, 0.0f,  0.3922f, 0.4f, 0.8f,//v2
         -0.25f,-0.3f, 0.0f, 0.3922f, 0.4f, 0.8f,//v3
         //parallelogram2/2 - Morado
         -0.05f,-0.3f, 0.0f, 0.3922f, 0.4f, 0.8f,//v1
         -0.25f,0.0f, 0.0f,  0.3922f, 0.4f, 0.8f,//v2
         -0.25f,-0.3f, 0.0f, 0.3922f, 0.4f, 0.8f,//v3
         //FirstLowTriangle - Verde claro
         -0.05f,-0.3f, 0.0f, 0.6078f, 0.7922f, 0.2f,//v1
         -0.25f,0.0f, 0.0f,  0.6078f, 0.7922f, 0.2f,//v2
           0.2f,0.0f, 0.0f,  0.6078f, 0.7922f, 0.2f,//v3
         //LowSquared1/2 - Rosado
         -0.05f,-0.5f, 0.0f, 0.9922f, 0.4078f, 0.4039f,//v1
         -0.05f,-0.3f, 0.0f, 0.9922f, 0.4078f, 0.4039f,//v2
         -0.25f,-0.3f, 0.0f, 0.9922f, 0.4078f, 0.4039f,//v3
         //LowSquared2/2 - Rosado
         -0.05f,-0.5f, 0.0f, 0.9922f, 0.4078f, 0.4039f,//v1
         -0.25f,-0.5f, 0.0f, 0.9922f, 0.4078f, 0.4039f,//v2
         -0.25f,-0.3f, 0.0f, 0.9922f, 0.4078f, 0.4039f,//v3
         //LastLowTriangle - Azul claro
         -0.1f,-0.5f, 0.0f, 0.1804f, 0.6118f, 0.9961f,//v1
         -0.1f,-0.7f, 0.0f, 0.1804f, 0.6118f, 0.9961f,//v2
         -0.3f,-0.7f, 0.0f, 0.1804f, 0.6118f, 0.9961f//v3
    };

    //Task3
    float offset = 0.5f;



    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.use();

        // Calcula el tiempo transcurrido
        float currentTime = glfwGetTime(); // Devuelve el tiempo desde que la aplicación inició

        //Send the time to the vertex shader
        ourShader.setFloat("time", currentTime);


        glBindVertexArray(VAO);
        const int vertex_amount = trianglesAmount * 3;
        for (size_t i = 0; i < vertex_amount; i+=3)
        {
            glDrawArrays(GL_TRIANGLES, i, i+3);	// this call should output an orange triangle
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
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
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
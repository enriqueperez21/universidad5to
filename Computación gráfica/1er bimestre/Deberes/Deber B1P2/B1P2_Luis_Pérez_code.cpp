#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
//dfsdf
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 700;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Function to create the Fragment Shader only with the color
const char* generateFragmentShader(const std::string& color) {
    std::string shaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4" + color + ";\n"
        "}\n";

    char* shaderCStr = new char[shaderSource.size() + 1];
    std::copy(shaderSource.begin(), shaderSource.end(), shaderCStr);
    shaderCStr[shaderSource.size()] = '\0';

    return shaderCStr;
}

// Variables de los colores
std::string verde =       "(0.1882f, 0.8f,    0.5f,    1.0f)";
std::string naranja =     "(0.9922f, 0.6078f, 0.2157f, 1.0f)";
std::string amarillo =    "(0.9922f, 0.8078f, 0.0039f, 1.0f)";
std::string morado =      "(0.3922f, 0.4f,    0.8f,    1.0f)";
std::string verdeClaro =  "(0.6078f, 0.7922f, 0.2f,    1.0f)";
std::string rosado =      "(0.9922f, 0.4078f, 0.4039f, 1.0f)";
std::string celeste =     "(0.1804f, 0.6118f, 0.9961f, 1.0f)";

// Function to create the shderProgram, using the color variable
static unsigned int createShaderProgram(unsigned int vertexShader, const std::string& color) {
    //Creamos el FragmentShaderSource usando el color
    const char* fragmentShaderSource = generateFragmentShader(color);
    //Declaramos el fragmentShader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Declaramos el shaderProgram
    unsigned int shaderProgram = glCreateProgram();

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // link the first program object
    // then link the second program object using a different fragment shader (but same vertex shader)
    // this is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    return shaderProgram;
};

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "0705052728 - Luis Enrique Pérez Señalin", NULL, NULL);
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
    // we skipped compile log checks this time for readability (if you do encounter issues, add the compile-checks! see previous code samples)
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int shaderProgramVerde =       createShaderProgram(vertexShader, verde);
    unsigned int shaderProgramNaranja =     createShaderProgram(vertexShader, naranja);
    unsigned int shaderProgramAmarillo =    createShaderProgram(vertexShader, amarillo);
    unsigned int shaderProgramMorado =      createShaderProgram(vertexShader, morado);
    unsigned int shaderProgramVerdeClaro =  createShaderProgram(vertexShader, verdeClaro);
    unsigned int shaderProgramRosado =      createShaderProgram(vertexShader, rosado);
    unsigned int shaderProgramCeleste =     createShaderProgram(vertexShader, celeste);
        
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    const int trianglesAmount = 9;
    float triangles[trianglesAmount][9] = {
        {
        //CenterTriangle - Amarillo
       -0.4f, 0.0f, 0.0f, //v1
        0.0f, 0.5f, 0.0f, //v2
        0.0f, 0.0f, 0.0f, //center
        },
        {
        //TopTriangle1 - Naranja
      -0.15f,0.65f, 0.0f, //v1
       0.15f,0.65f, 0.0f, //v2
       0.0f, 0.5f,  0.0f, //v3
        },
        {
        //TopTriangle2 - Verde
       -0.3f,0.65f, 0.0f, //v1
        0.3f,0.65f, 0.0f, //v2
        0.0f, 0.9f, 0.0f, //v3
        },
        {
        //parallelogram1/2 - Morado
       -0.45f,0.0f, 0.0f, //v1
       -0.25f,0.0f, 0.0f, //v2
      -0.25f,-0.3f, 0.0f, //v3
        },
        {
        //parallelogram2/2 - Morado
       -0.05f,-0.3f, 0.0f, //v1
       -0.25f,0.0f, 0.0f, //v2
      -0.25f,-0.3f, 0.0f, //v3
        },
        {
        //FirstLowTriangle - Verde claro
      -0.05f,-0.3f, 0.0f, //v1
       -0.25f,0.0f, 0.0f, //v2
         0.2f,0.0f, 0.0f, //v3
        },
        {
        //LowSquared1/2 - Rosado
      -0.05f,-0.5f, 0.0f, //v1
      -0.05f,-0.3f, 0.0f, //v2
      -0.25f,-0.3f, 0.0f, //v3
        },
        {
        //LowSquared2/2 - Rosado
      -0.05f,-0.5f, 0.0f, //v1
      -0.25f,-0.5f, 0.0f, //v2
      -0.25f,-0.3f, 0.0f, //v3
        },
        {
        //LastLowTriangle - Azul claro
       -0.1f,-0.5f, 0.0f, //v1
       -0.1f,-0.7f, 0.0f, //v2
       -0.3f,-0.7f, 0.0f, //v3
        }
    };

    unsigned int trianglesColors[] = {
        shaderProgramAmarillo,
        shaderProgramNaranja,
        shaderProgramVerde,
        shaderProgramMorado,
        shaderProgramMorado,
        shaderProgramVerdeClaro,
        shaderProgramRosado,
        shaderProgramRosado,
        shaderProgramCeleste
    };

    unsigned int VBOs[trianglesAmount], VAOs[trianglesAmount];
    glGenVertexArrays(trianglesAmount, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(trianglesAmount, VBOs);

    for (size_t i = 0; i < trianglesAmount; i++)
    {
        // --------------------
        glBindVertexArray(VAOs[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[i]), triangles[i], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
        glEnableVertexAttribArray(0);
        // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
    }

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

        //We use a for to draw each triangle
        for (size_t i = 0; i < trianglesAmount; i++)
        {
            // now when we draw the triangle we first use the vertex and orange fragment shader from the first program
            glUseProgram(trianglesColors[i]);
            // draw the first triangle using the data from our first VAO
            glBindVertexArray(VAOs[i]);
            glDrawArrays(GL_TRIANGLES, 0, 3);	// this call should output an orange triangle
        }
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(trianglesAmount, VAOs);
    glDeleteBuffers(trianglesAmount, VBOs);

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
    //if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
//   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
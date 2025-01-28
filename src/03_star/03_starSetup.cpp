/* **************************************************************************************************** */

#include "../../headers/setup.hpp"

/* **************************************************************************************************** */

const int triangles = 0;
const int numVAOs = 1;

const int arrayBuffer = 0;
const int numBuffers = 1;
const int vPosition = 0;

GLuint VAOs[numVAOs];
GLuint buffers[numBuffers];

GLuint numVertices = 0;

/* **************************************************************************************************** */

void startup(){
    glGenVertexArrays(numVAOs, VAOs);
    glBindVertexArray(VAOs[triangles]);

    GLfloat vertices[][2] = {
        {+0.00f, +1.00f}, 
        {-0.25f, +0.40f},
        {-1.00f, +0.40f}, 
        {-0.50f, -0.25f}, 
        {-1.00f, -1.00f},
        {+0.00f, -0.50f},
        {+1.00f, -1.00f},
        {+0.50f, -0.25f},
        {+1.00f, +0.40f},
        {+0.25f, +0.40f}
    };

    glCreateBuffers(numBuffers, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[arrayBuffer]);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);

    struct shader shaders[] = {
        {GL_VERTEX_SHADER, "../shaders/03_star/star.vert"},
        {GL_FRAGMENT_SHADER, "../shaders/03_star/star.frag"},
        {GL_NONE, NULL}
    };

    GLuint program = loadShader(shaders);
    glUseProgram(program);

    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

/* **************************************************************************************************** */

void render(double currentTime){
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};

    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray(VAOs[triangles]);
    glDrawArrays(GL_LINE_LOOP, 0, numVertices);
}

/* **************************************************************************************************** */

void shutdown(){

}

/* **************************************************************************************************** */

int run(){
    int running = 1;

    while (running) {
        render(glfwGetTime());

        glfwSwapBuffers(window);
        glfwPollEvents();

        running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
        running &= (glfwWindowShouldClose(window) != GL_TRUE);
   }

   return 1;
}

/* **************************************************************************************************** */
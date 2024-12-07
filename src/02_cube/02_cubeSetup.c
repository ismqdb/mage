/* **************************************************************************************************** */

#include "../../headers/setup.h"

/* **************************************************************************************************** */

#define BUFFER_OFFSET(a) ((void*)(a))

enum VAO_IDs {Triangles, NumVAOs = 1};
enum Buffer_IDs {ArrayBuffer, NumBuffers = 1};
enum Attrib_IDs {vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 4;

/* **************************************************************************************************** */

void startup(){
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    GLfloat vertices[][2] = {
        {-0.9f, 0.9f}, {-0.9f, -0.9f}, {0.9f, -0.9f}, {0.9f, 0.9f}
    };

    glCreateBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);

    struct shader shaders[] = {
        {GL_VERTEX_SHADER, "../shaders/02_cube/cube.vert"},
        {GL_FRAGMENT_SHADER, "../shaders/02_cube/cube.frag"},
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

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, NumVertices);
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
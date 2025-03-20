/* **************************************************************************************************** */

#include "./01_triangle.hpp"

/* **************************************************************************************************** */

int main(){
    triangleApp triangleApp;

    triangleApp.gameLoop();
}

/* **************************************************************************************************** */

triangleApp::triangleApp() : app(){
    memset(this->pressed, 0, GLFW_KEY_LAST);

    glfwSetup();
    openglSetup();

    this->modelMatrix = glm::mat4(1.0f);
    triangle_1 = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    triangle_2 = glm::translate(modelMatrix, glm::vec3(0.25f, 0.0f, 0.0f));
    triangle_3 = glm::translate(modelMatrix, glm::vec3(0.5f, 0.0f, 0.0f));
    triangle_4 = glm::translate(modelMatrix, glm::vec3(0.75f, 0.0f, 0.0f));
}

triangleApp::~triangleApp() {
    openglTeardown();
    glfwTeardown();
}

/* **************************************************************************************************** */

void triangleApp::openglSetup(){
    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glCreateBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions)+sizeof(vertexColors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), vertexPositions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions), sizeof(vertexColors), vertexColors);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(vertexPositions));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

/* **************************************************************************************************** */

void triangleApp::render(){    
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

    glUniformMatrix4fv(translationMatrixPosition, 1, GL_FALSE, glm::value_ptr(triangle_1));
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUniformMatrix4fv(translationMatrixPosition, 1, GL_FALSE, glm::value_ptr(triangle_2));
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

    glUniformMatrix4fv(translationMatrixPosition, 1, GL_FALSE, glm::value_ptr(triangle_3));
    glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 0);

    glUniformMatrix4fv(translationMatrixPosition, 1, GL_FALSE, glm::value_ptr(triangle_4));
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);
}

/* **************************************************************************************************** */

void triangleApp::openglTeardown(){
    glUseProgram(0);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, vao);
    glDeleteBuffers(1, vbo);
}

/* **************************************************************************************************** */

void triangleApp::gameLoop(){
    int running = 1;

    shader shaders[] = {
        {GL_VERTEX_SHADER, "../shaders/01_triangle/01_triangle.vert"},
        {GL_FRAGMENT_SHADER, "../shaders/01_triangle/01_triangle.frag"},
        {GL_NONE, NULL}
    };

    program = loadShader(shaders); 
    glUseProgram(program);

    translationMatrixPosition = glGetUniformLocation(program, "translationMatrix");

    while (running) {
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        update();

        running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
        running &= (glfwWindowShouldClose(window) != GL_TRUE);
   }
}

/* **************************************************************************************************** */

void triangleApp::glfwSetup(){
    glfwInit();

    info.windowWidth = 800;
    info.windowHeight = 600;

    const char title[] = "mage";
    info.title = title;
    
    #ifdef __APPLE__
        info.majorVersion = 3;
        info.minorVersion = 2;
    #else
        info.majorVersion = 4;
        info.minorVersion = 5;
    #endif

    info.samples = 0;
    info.flags.all = 0;
    info.flags.cursor = 1;

    #ifdef _DEBUG
        info.flags.debug = 1;
    #endif

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    window = glfwCreateWindow(info.windowWidth, info.windowHeight, info.title.c_str(), 
        info.flags.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);

    glfwSetWindowSizeCallback(window, onResize);
    glfwSetKeyCallback(window, onKey);
    glfwSetMouseButtonCallback(window, onMouseButton);
    glfwSetCursorPosCallback(window, onMouseMove);
    glfwSetScrollCallback(window, onMouseWheel);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSetKeyCallback(window, onKey);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
}

/* **************************************************************************************************** */

void triangleApp::glfwTeardown(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

/* **************************************************************************************************** */

void triangleApp::onResize(GLFWwindow* window, int width, int height){
    triangleApp *pThis = (triangleApp*)glfwGetWindowUserPointer(window);
    pThis->resizeWindow(width, height);
}

void triangleApp::resizeWindow(int width, int height){
    glViewport(0, 0, width, height);
    aspectRatio = float(width)/float(height);
}

/* **************************************************************************************************** */

void triangleApp::onKey(GLFWwindow* window, int key, int scancode, int action, int mods){
    triangleApp *pThis = (triangleApp*)glfwGetWindowUserPointer(window);
    pThis->keyPress(key, scancode, action, mods);
}

void triangleApp::keyPress(int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_UNKNOWN)
        return;

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);
    
    for(int i = 0; i < GLFW_KEY_LAST; i++)
        if(action == GLFW_PRESS && i == key)
            pressed[key] = true;
        else if(action == GLFW_RELEASE && i == key)
            pressed[key] = false;
}

/* **************************************************************************************************** */

void triangleApp::onMouseButton(GLFWwindow* window, int button, int action, int mods){
    triangleApp *pThis = (triangleApp*)glfwGetWindowUserPointer(window);
    pThis->mouseClick(button, action, mods);
}

void triangleApp::mouseClick(int button, int action, int mods){

}

/* **************************************************************************************************** */

void triangleApp::onMouseMove(GLFWwindow* window, double x, double y){
    triangleApp *pThis = (triangleApp*)glfwGetWindowUserPointer(window);
    pThis->mouseMove(x, y);
}

void triangleApp::mouseMove(double x, double y){

}

/* **************************************************************************************************** */

void triangleApp::onMouseWheel(GLFWwindow* window, double xoffset, double yoffset){
    triangleApp *pThis = (triangleApp*)glfwGetWindowUserPointer(window);
    pThis->mouseWheel(xoffset, yoffset);
}

void triangleApp::mouseWheel(double xoffset, double yoffset){

}

/* **************************************************************************************************** */

void triangleApp::setVsync(int enable){
    info.flags.vsync = enable ? 1 : 0;
    glfwSwapInterval((int)info.flags.vsync);
}

/* **************************************************************************************************** */

void triangleApp::getMousePosition(int *x, int *y){
    double dx, dy;
    glfwGetCursorPos(window, &dx, &dy);

    *x = (int)(floor(dx));
    *y = (int)(floor(dy));
}

/* **************************************************************************************************** */

void GLAPIENTRY
triangleApp::MessageCallback(GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam){
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

/* **************************************************************************************************** */

void triangleApp::update(){
}

/* **************************************************************************************************** */
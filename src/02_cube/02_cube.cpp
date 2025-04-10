/* **************************************************************************************************** */

#include "./02_cube.hpp"

/* **************************************************************************************************** */

int main(){
    cubeApp cubeApp;

    cubeApp.gameLoop();
}

/* **************************************************************************************************** */

cubeApp::cubeApp() : app(){
    memset(this->pressed, 0, GLFW_KEY_LAST);

    glfwSetup();
}

cubeApp::~cubeApp() {
    openglTeardown();
    glfwTeardown();
}

/* **************************************************************************************************** */

void cubeApp::openglSetup(){
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
}

/* **************************************************************************************************** */

void cubeApp::render(){    
    GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
    GLfloat one = 1.0f;

    glClearBufferfv(GL_COLOR, 0, green);
    glClearBufferfv(GL_DEPTH, 0, &one);

    glUseProgram(program);

    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

/* **************************************************************************************************** */

void cubeApp::openglTeardown(){
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
    glDeleteBuffers(1, &buffer);
}

/* **************************************************************************************************** */

void cubeApp::gameLoop(){
    int running = 1;

    mage::shader shaders[] = {
        {GL_VERTEX_SHADER, "../shaders/02_cube/02_cube.vert"},
        {GL_FRAGMENT_SHADER, "../shaders/02_cube/02_cube.frag"},
        {GL_NONE, NULL}
    };

    projectionMatrix = glm::perspective(
        (float)glm::radians((float)fov), 
        (float)info.windowWidth / (float)info.windowHeight, 
        0.1f, 
        100.0f
    );

    viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f), 
        glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    modelMatrix = glm::mat4(1.0f);

    program = mage::loadShader(shaders); 
    glUseProgram(program);

    projectionMatrixLocation = glGetUniformLocation(program, "projection");
    viewMatrixLocation = glGetUniformLocation(program, "view");
    modelMatrixLocation = glGetUniformLocation(program, "model");

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    openglSetup();

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

void cubeApp::glfwSetup(){
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

void cubeApp::glfwTeardown(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

/* **************************************************************************************************** */

void cubeApp::onResize(GLFWwindow* window, int width, int height){
    cubeApp *pThis = (cubeApp*)glfwGetWindowUserPointer(window);
    pThis->resizeWindow(width, height);
}

void cubeApp::resizeWindow(int width, int height){
    this->info.windowWidth = width;
    this->info.windowHeight = height;

    glViewport(0, 0, width, height);
    aspectRatio = float(info.windowWidth)/float(info.windowHeight); 
    
    projectionMatrix = glm::perspective(
        (float)glm::radians((float)fov), 
        (float)info.windowWidth / (float)info.windowHeight, 
        aspectRatio, 
        100.0f
    );
}

/* **************************************************************************************************** */

void cubeApp::onKey(GLFWwindow* window, int key, int scancode, int action, int mods){
    cubeApp *pThis = (cubeApp*)glfwGetWindowUserPointer(window);
    pThis->keyPress(key, scancode, action, mods);
}

void cubeApp::keyPress(int key, int scancode, int action, int mods){
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

void cubeApp::onMouseButton(GLFWwindow* window, int button, int action, int mods){
    cubeApp *pThis = (cubeApp*)glfwGetWindowUserPointer(window);
    pThis->mouseClick(button, action, mods);
}

void cubeApp::mouseClick(int button, int action, int mods){

}

/* **************************************************************************************************** */

void cubeApp::onMouseMove(GLFWwindow* window, double x, double y){
    cubeApp *pThis = (cubeApp*)glfwGetWindowUserPointer(window);
    pThis->mouseMove(x, y);
}

void cubeApp::mouseMove(double x, double y){

}

/* **************************************************************************************************** */

void cubeApp::onMouseWheel(GLFWwindow* window, double xoffset, double yoffset){
    cubeApp *pThis = (cubeApp*)glfwGetWindowUserPointer(window);
    pThis->mouseWheel(xoffset, yoffset);
}

void cubeApp::mouseWheel(double xoffset, double yoffset){

}

/* **************************************************************************************************** */

void cubeApp::setVsync(int enable){
    info.flags.vsync = enable ? 1 : 0;
    glfwSwapInterval((int)info.flags.vsync);
}

/* **************************************************************************************************** */

void cubeApp::getMousePosition(int *x, int *y){
    double dx, dy;
    glfwGetCursorPos(window, &dx, &dy);

    *x = (int)(floor(dx));
    *y = (int)(floor(dy));
}

/* **************************************************************************************************** */

void GLAPIENTRY
cubeApp::MessageCallback(GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam){
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
    
    int error = glGetError();

    if(error != GL_NO_ERROR)
        errorAbort(error, message);
}

/* **************************************************************************************************** */

void cubeApp::update(){
    double deltaMove = 0.025;

    for(int i = 0; i < GLFW_KEY_LAST; i++){
        if(!pressed[i])
            continue;

        switch(i){
            case GLFW_KEY_A:
                modelMatrix = glm::rotate(
                    modelMatrix,
                    (float)glfwGetTime(),
                    glm::vec3(1.0f, 0.0f, 0.0f)
                );
                break;

            case GLFW_KEY_D:
                modelMatrix = glm::rotate(
                    modelMatrix,
                    (float)glfwGetTime(),
                    glm::vec3(0.0f, 0.0f, 1.0f)
                );
                break;

            case GLFW_KEY_W:
                modelMatrix = glm::rotate(
                    modelMatrix,
                    (float)glfwGetTime(),
                    glm::vec3(0.0f, 1.0f, 0.0f)
                );
                break;

            case GLFW_KEY_LEFT:
                modelMatrix = glm::translate(
                    modelMatrix,
                    glm::vec3(-deltaMove, 0.0, 0.0)
                );
                break;

            case GLFW_KEY_RIGHT:
                modelMatrix = glm::translate(
                    modelMatrix,
                    glm::vec3(deltaMove, 0.0f, 0.0f)
                );
                break;

            case GLFW_KEY_UP:
                modelMatrix = glm::translate(
                    modelMatrix,
                    glm::vec3(0.0f, deltaMove, 0.0f)
                );
                break;

            case GLFW_KEY_DOWN:
                modelMatrix = glm::translate(
                    modelMatrix,
                    glm::vec3(0.0f, -deltaMove, 0.0f)
                );
                break;
        }
    }
}

/* **************************************************************************************************** */
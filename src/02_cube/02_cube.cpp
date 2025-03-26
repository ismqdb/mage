/* **************************************************************************************************** */

#include "./02_cube.hpp"

/* **************************************************************************************************** */

int main(){
    cubeApp triangleApp;

    triangleApp.gameLoop();
}

/* **************************************************************************************************** */

cubeApp::cubeApp() : app(){
    memset(this->pressed, 0, GLFW_KEY_LAST);

    glfwSetup();
    openglSetup();
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

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

/* **************************************************************************************************** */

void cubeApp::render(){    
    GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
    GLfloat one = 1.0f;

    glViewport(0, 0, info.windowWidth, info.windowHeight);
    glClearBufferfv(GL_COLOR, 0, green);
    glClearBufferfv(GL_DEPTH, 0, &one);

    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projMatrix));
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

    program = mage::loadShader(shaders); 
    glUseProgram(program);

    mvLocation = glGetUniformLocation(program, "mvMatrix");
    projLocation = glGetUniformBlockIndex(program, "projLocation");

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
    glViewport(0, 0, width, height);
    aspectRatio = float(width)/float(height);


    projMatrix = glm::perspective(50.0f, aspectRatio, 0.1f, 1000.0f);
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
}

/* **************************************************************************************************** */

void cubeApp::update(){
}

/* **************************************************************************************************** */
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
}

triangleApp::~triangleApp() {
    glfwTeardown();
}

/* **************************************************************************************************** */

void triangleApp::openglSetup(){
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glCreateBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, 0);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
}

/* **************************************************************************************************** */

void triangleApp::render(){
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};

    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray(vao[0]);
    glPointSize(5);
    glDrawArrays(GL_TRIANGLES, 0, 3);      
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

    const char title[] = "MAGE";
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

    openglSetup();
}

/* **************************************************************************************************** */

void triangleApp::glfwTeardown(){
    openglTeardown();

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
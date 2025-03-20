/* **************************************************************************************************** */

#include "./00_dot.hpp"

/* **************************************************************************************************** */

int main(){
    dotApp dotApp;

    dotApp.gameLoop();
}

/* **************************************************************************************************** */

dotApp::dotApp() : app(){
    numVAOs = 1;
    numBuffers = 1;

    VAOs[0] = {0};
    buffers[0] = {0};

    numVertices = 0;

    vertices[0][0] = 0.25f;
    vertices[0][1] = 0.40f;

    numVertices = sizeof(vertices[0])/sizeof(GLfloat) / 2;

    memset(this->pressed, 0, GLFW_KEY_LAST);

    glfwSetup();
}

dotApp::~dotApp() {
    glfwTeardown();
}

/* **************************************************************************************************** */

void dotApp::openglSetup(){
    glGenVertexArrays(numVAOs, VAOs);
    glBindVertexArray(VAOs[0]);

    glCreateBuffers(numBuffers, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(0);
}

/* **************************************************************************************************** */

void dotApp::render(){
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};

    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray(VAOs[0]);
    glPointSize(this->pointSize);
    glDrawArrays(GL_POINTS, 0, numVertices);        // Points
}

/* **************************************************************************************************** */

void dotApp::openglTeardown(){

}

/* **************************************************************************************************** */

void dotApp::gameLoop(){
    int running = 1;

    shader shaders[] = {
        {GL_VERTEX_SHADER, "../shaders/00_dot/00_dot.vert"},
        {GL_FRAGMENT_SHADER, "../shaders/00_dot/00_dot.frag"},
        {GL_NONE, NULL}
    };

    GLuint program = loadShader(shaders);
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

void dotApp::glfwSetup(){
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

    openglSetup();
}

/* **************************************************************************************************** */

void dotApp::glfwTeardown(){
    openglTeardown();

    glfwDestroyWindow(window);
    glfwTerminate();
}

/* **************************************************************************************************** */

void dotApp::onResize(GLFWwindow* window, int w, int h){
    dotApp *pThis = (dotApp*)glfwGetWindowUserPointer(window);
    pThis->resizeWindow(w, h);
}

void dotApp::resizeWindow(int x, int y){
    info.windowWidth = x;
    info.windowHeight = y;
}

/* **************************************************************************************************** */

void dotApp::onKey(GLFWwindow* window, int key, int scancode, int action, int mods){
    dotApp *pThis = (dotApp*)glfwGetWindowUserPointer(window);
    pThis->keyPress(key, scancode, action, mods);
}

void dotApp::keyPress(int key, int scancode, int action, int mods){
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

void dotApp::onMouseButton(GLFWwindow* window, int button, int action, int mods){
    dotApp *pThis = (dotApp*)glfwGetWindowUserPointer(window);
    pThis->mouseClick(button, action, mods);
}

void dotApp::mouseClick(int button, int action, int mods){

}

/* **************************************************************************************************** */

void dotApp::onMouseMove(GLFWwindow* window, double x, double y){
    dotApp *pThis = (dotApp*)glfwGetWindowUserPointer(window);
    pThis->mouseMove(x, y);
}

void dotApp::mouseMove(double x, double y){

}

/* **************************************************************************************************** */

void dotApp::onMouseWheel(GLFWwindow* window, double xoffset, double yoffset){
    dotApp *pThis = (dotApp*)glfwGetWindowUserPointer(window);
    pThis->mouseWheel(xoffset, yoffset);
}

void dotApp::mouseWheel(double xoffset, double yoffset){

}

/* **************************************************************************************************** */

void dotApp::setVsync(int enable){
    info.flags.vsync = enable ? 1 : 0;
    glfwSwapInterval((int)info.flags.vsync);
}

/* **************************************************************************************************** */

void dotApp::getMousePosition(int *x, int *y){
    double dx, dy;
    glfwGetCursorPos(window, &dx, &dy);

    *x = (int)(floor(dx));
    *y = (int)(floor(dy));
}

/* **************************************************************************************************** */

void GLAPIENTRY
dotApp::MessageCallback(GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam){

}

/* **************************************************************************************************** */

void dotApp::update(){
    for(int i = 0; i < GLFW_KEY_LAST; i++){
        if(!pressed[i])
            continue;

        switch(i){
            case GLFW_KEY_LEFT:
                this->vertices[0][0] -= 0.01;
                break;

            case GLFW_KEY_RIGHT:
                this->vertices[0][0] += 0.01;
                break;

            case GLFW_KEY_UP:
                this->vertices[0][1] += 0.01;
                break;

            case GLFW_KEY_DOWN:
                this->vertices[0][1] -= 0.01;
                break;

            case GLFW_KEY_A:
                this->pointSize++;
                break;
            
            case GLFW_KEY_D:
                this->pointSize--;
                break;
        }
    }

    this->openglSetup();
}

/* **************************************************************************************************** */
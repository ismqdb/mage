/* **************************************************************************************************** */

#include "./00_dot.hpp"

/* **************************************************************************************************** */

int main(){
    dotApp dotApp;

    dotApp.run();
}

/* **************************************************************************************************** */

dotApp::dotApp() : app(){
    triangles = 0;
    numVAOs = 1;

    arrayBuffer = 0;
    numBuffers = 1;
    vPosition = 0;

    VAOs[0] = {0};
    buffers[0] = {0};

    numVertices = 0;

    init();
}

dotApp::~dotApp() {
    deinit();
}

/* **************************************************************************************************** */

void dotApp::startup(){
    glGenVertexArrays(numVAOs, VAOs);
    glBindVertexArray(VAOs[triangles]);

    GLfloat vertices[][2] = {
        {+0.25f, +0.40f},   // 1
    };

    numVertices = sizeof(vertices[0])/sizeof(GLfloat) / 2;

    glCreateBuffers(numBuffers, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[arrayBuffer]);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);

    shader shaders[] = {
        {GL_VERTEX_SHADER, "../shaders/00_dot/dot.vert"},
        {GL_FRAGMENT_SHADER, "../shaders/00_dot/dot.frag"},
        {GL_NONE, NULL}
    };

    GLuint program = loadShader(shaders);
    glUseProgram(program);

    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(vPosition);
}

/* **************************************************************************************************** */

void dotApp::render(){
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};

    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray(VAOs[triangles]);
    glPointSize(5);
    glDrawArrays(GL_POINTS, 0, numVertices);        // Points
}

/* **************************************************************************************************** */

void dotApp::shutdown(){

}

/* **************************************************************************************************** */

void dotApp::run(){
    int running = 1;

    while (running) {
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
        running &= (glfwWindowShouldClose(window) != GL_TRUE);
   }
}

/* **************************************************************************************************** */

void dotApp::init(){
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

    startup();
}

/* **************************************************************************************************** */

void dotApp::deinit(){
    shutdown();

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
    if(key == GLFW_KEY_LEFT){
        
    }

    if(key == GLFW_KEY_RIGHT){

    }
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
dotApp::MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}
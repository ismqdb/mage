/* **************************************************************************************************** */

#include "./00_dot.hpp"

/* **************************************************************************************************** */

int main(){
    dotApp app{};

    app.run();
}

/* **************************************************************************************************** */

dotApp::dotApp(){
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
        {+0.00f, +1.00f},   // 2
        {-0.25f, +0.40f},   // 3

        {-0.25f, +0.40f},   // 3
        {-1.00f, +0.40f},   // 4
        {-0.50f, -0.25f},   // 5

        {-0.50f, -0.25f},   // 5
        {-1.00f, -1.00f},   // 6
        {+0.00f, -0.50f},   // 7

        {+0.00f, -0.50f},   // 7
        {+1.00f, -1.00f},   // 8
        {+0.50f, -0.25f},   // 9

        {+0.50f, -0.25f},   // 9
        {+1.00f, +0.40f},   // 10
        {+0.25f, +0.40f},   // 1
    };

    numVertices = sizeof(vertices)/sizeof(GLfloat);

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

    window = glfwCreateWindow(info.windowWidth, info.windowHeight, info.title.c_str(), 
        info.flags.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

    glfwSetWindowUserPointer(window, this);

    glfwSetWindowSizeCallback(window, onResize);
    glfwSetKeyCallback(window, onKey);
    glfwSetMouseButtonCallback(window, onMouseButton);
    glfwSetCursorPosCallback(window, onMouseMove);
    glfwSetScrollCallback(window, onMouseWheel);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSetKeyCallback(window, onKey);

    glfwMakeContextCurrent(window);

    startup();
    
}

/* **************************************************************************************************** */

void dotApp::deinit(){
    shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();
}

/* **************************************************************************************************** */
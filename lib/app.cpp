/* **************************************************************************************************** */

#include "../headers/app.hpp"

/* **************************************************************************************************** */

void app::onResize(GLFWwindow* window, int w, int h){
    info.windowWidth = w;
    info.windowHeight = h;
}

/* **************************************************************************************************** */

void app::onKey(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_LEFT){
        
    }

    if(key == GLFW_KEY_RIGHT){

    }
}

/* **************************************************************************************************** */

void app::onMouseButton(GLFWwindow* window, int button, int action, int mods){}
void app::onMouseMove(GLFWwindow* window, double x, double y){}
void app::onMouseWheel(GLFWwindow* window, double xoffset, double yoffset){}

/* **************************************************************************************************** */

void app::setVsync(int enable){
    info.flags.vsync = enable ? 1 : 0;
    glfwSwapInterval((int)info.flags.vsync);
}

/* **************************************************************************************************** */

void app::getMousePosition(int *x, int *y){
    double dx, dy;
    glfwGetCursorPos(window, &dx, &dy);

    *x = (int)(floor(dx));
    *y = (int)(floor(dy));
}

/* **************************************************************************************************** */

void app::init(){
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

void app::deinit(){
    shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();
}

/* **************************************************************************************************** */
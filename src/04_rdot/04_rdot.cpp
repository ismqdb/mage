/* **************************************************************************************************** */

#include "./04_rdot.hpp"

/* **************************************************************************************************** */

i32 main(){
    rdot rdotApp;

    //mage::circle *circle1 = new mage::circle(mage::vec3{.x = 0.0f, .y = +0.5f, .z = 0.0f}, 1.0f/4, 3);

    mage::triangle *triangle1 = new mage::triangle{
        mage::vec3{.x = +0.00, .y = +0.30, .z = 0.0},
        mage::vec3{.x = -0.50, .y = -0.30, .z = 0.0},
        mage::vec3{.x = +0.50, .y = +0.50, .z = 0.0}
    };

    //circle1->setProgram(rdotApp.getProgram());
    triangle1->setProgram(rdotApp.getProgram());

    //rdotApp.addObject(circle1);
    rdotApp.addObject(triangle1);

    rdotApp.gameLoop();

    //delete circle1;
    delete triangle1;
}

/* **************************************************************************************************** */

rdot::rdot() : app(){
    memset(this->pressed, 0, GLFW_KEY_LAST);

    glfwSetup();
}

rdot::~rdot() {
    glfwTeardown();
}

/* **************************************************************************************************** */

void rdot::addObject(mage::mageObject *obj){
    objects.insert(obj);
}

/* **************************************************************************************************** */

GLint rdot::getProgram(){
    return program;
}

/* **************************************************************************************************** */

void rdot::openglSetup(){
    
}

/* **************************************************************************************************** */

void rdot::render(){
    GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
    GLfloat one = 1.0f;

    glClearBufferfv(GL_COLOR, 0, green);
    glClearBufferfv(GL_DEPTH, 0, &one);

    glUseProgram(program);

    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glPointSize(10);

    for(int i = 0; i < objects.size(); i++)
        (*objects[i])->render();
}

/* **************************************************************************************************** */

void rdot::openglTeardown(){

}

/* **************************************************************************************************** */

void rdot::gameLoop(){
    i32 running = 1;

    mage::shader shaders[] = {
        {GL_VERTEX_SHADER, "../shaders/04_rdot/04_rdot.vert"},
        {GL_FRAGMENT_SHADER, "../shaders/04_rdot/04_rdot.frag"},
        {GL_NONE, NULL}
    };

    projectionMatrix = glm::perspective(
        (f32)glm::radians((f32)fov), 
        (f32)info.windowWidth / (f32)info.windowHeight, 
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
    glFrontFace(GL_CCW);
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

void rdot::glfwSetup(){
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    if (!glfwInit()) {
        const char* description;
        int code = glfwGetError(&description);
        printf("GLFW init failed (%d): %s\n", code, description);
        abort();
    }

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

void rdot::glfwTeardown(){
    openglTeardown();

    glfwDestroyWindow(window);
    glfwTerminate();
}

/* **************************************************************************************************** */

void rdot::onResize(GLFWwindow* window, i32 w, i32 h){
    rdot *pThis = (rdot*)glfwGetWindowUserPointer(window);
    pThis->resizeWindow(w, h);
}

void rdot::resizeWindow(i32 x, i32 y){
    info.windowWidth = x;
    info.windowHeight = y;
}

/* **************************************************************************************************** */

void rdot::onKey(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods){
    rdot *pThis = (rdot*)glfwGetWindowUserPointer(window);
    pThis->keyPress(key, scancode, action, mods);
}

void rdot::keyPress(i32 key, i32 scancode, i32 action, i32 mods){
    if(key == GLFW_KEY_UNKNOWN)
        return;

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);
    
    for(i32 i = 0; i < GLFW_KEY_LAST; i++)
        if(action == GLFW_PRESS && i == key)
            pressed[key] = true;
        else if(action == GLFW_RELEASE && i == key)
            pressed[key] = false;
}

/* **************************************************************************************************** */

void rdot::onMouseButton(GLFWwindow* window, i32 button, i32 action, i32 mods){
    rdot *pThis = (rdot*)glfwGetWindowUserPointer(window);
    pThis->mouseClick(button, action, mods);
}

void rdot::mouseClick(i32 button, i32 action, i32 mods){

}

/* **************************************************************************************************** */

void rdot::onMouseMove(GLFWwindow* window, f64 x, f64 y){
    rdot *pThis = (rdot*)glfwGetWindowUserPointer(window);
    pThis->mouseMove(x, y);
}

void rdot::mouseMove(f64 x, f64 y){

}

/* **************************************************************************************************** */

void rdot::onMouseWheel(GLFWwindow* window, f64 xoffset, f64 yoffset){
    rdot *pThis = (rdot*)glfwGetWindowUserPointer(window);
    pThis->mouseWheel(xoffset, yoffset);
}

void rdot::mouseWheel(f64 xoffset, f64 yoffset){

}

/* **************************************************************************************************** */

void rdot::setVsync(i32 enable){
    info.flags.vsync = enable ? 1 : 0;
    glfwSwapInterval((i32)info.flags.vsync);
}

/* **************************************************************************************************** */

void rdot::getMousePosition(i32 *x, i32 *y){
    f64 dx, dy;
    glfwGetCursorPos(window, &dx, &dy);

    *x = (i32)(floor(dx));
    *y = (i32)(floor(dy));
}

/* **************************************************************************************************** */

void GLAPIENTRY
rdot::MessageCallback(GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam){

}

/* **************************************************************************************************** */

void rdot::update(){
    for(i32 i = 0; i < GLFW_KEY_LAST; i++){
        if(!pressed[i])
            continue;

        switch(i){
            case GLFW_KEY_LEFT:
                break;

            case GLFW_KEY_RIGHT:

                break;

            case GLFW_KEY_UP:
                break;

            case GLFW_KEY_DOWN:

                break;

            case GLFW_KEY_A:

                break;
            
            case GLFW_KEY_D:

                break;
        }
    }
}

/* **************************************************************************************************** */
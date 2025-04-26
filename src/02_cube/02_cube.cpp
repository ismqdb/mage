/* **************************************************************************************************** */

#include "./02_cube.hpp"

/* **************************************************************************************************** */

i32 main(){
    cubeApp cubeApp;

    cubeApp.gameLoop();
}

/* **************************************************************************************************** */

cubeApp::cubeApp() : app(){
    memset(this->pressed, 0, GLFW_KEY_LAST);

    glfwSetup();
    initPoints();
}

cubeApp::~cubeApp() {
    openglTeardown();
    glfwTeardown();
}

/* **************************************************************************************************** */

void cubeApp::initPoints(){
    vertexPositions.insertPoint(-0.25f, -0.25f, -0.25f, 1.0f);
    vertexPositions.insertPoint(-0.25f,  0.25f, -0.25f, 1.0f);
    vertexPositions.insertPoint(+0.25f, -0.25f, -0.25f, 1.0f);
    vertexPositions.insertPoint(+0.25f,  0.25f, -0.25f, 1.0f);
    vertexPositions.insertPoint(+0.25f, -0.25f,  0.25f, 1.0f);
    vertexPositions.insertPoint(+0.25f,  0.25f,  0.25f, 1.0f);
    vertexPositions.insertPoint(+0.25f, -0.25f,  0.25f, 1.0f);
    vertexPositions.insertPoint(-0.25f,  0.25f,  0.25f, 1.0f);
}

/* **************************************************************************************************** */

void cubeApp::openglSetup(){
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions.raw()), vertexPositions.raw(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);
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

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
}

/* **************************************************************************************************** */

void cubeApp::openglTeardown(){
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
    glDeleteBuffers(1, &positionBuffer);
}

/* **************************************************************************************************** */

void cubeApp::gameLoop(){
    i32 running = 1;

    mage::shader shaders[] = {
        {GL_VERTEX_SHADER, "../shaders/02_cube/02_cube.vert"},
        {GL_FRAGMENT_SHADER, "../shaders/02_cube/02_cube.frag"},
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

void cubeApp::onResize(GLFWwindow* window, i32 width, i32 height){
    cubeApp *pThis = (cubeApp*)glfwGetWindowUserPointer(window);
    pThis->resizeWindow(width, height);
}

void cubeApp::resizeWindow(i32 width, i32 height){
    this->info.windowWidth = width;
    this->info.windowHeight = height;

    glViewport(0, 0, width, height);
    aspectRatio = f32(info.windowWidth)/f32(info.windowHeight); 
    
    projectionMatrix = glm::perspective(
        (f32)glm::radians((f32)fov), 
        (f32)info.windowWidth / (f32)info.windowHeight, 
        aspectRatio, 
        100.0f
    );
}

/* **************************************************************************************************** */

void cubeApp::onKey(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods){
    cubeApp *pThis = (cubeApp*)glfwGetWindowUserPointer(window);
    pThis->keyPress(key, scancode, action, mods);
}

void cubeApp::keyPress(i32 key, i32 scancode, i32 action, i32 mods){
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

void cubeApp::onMouseButton(GLFWwindow* window, i32 button, i32 action, i32 mods){
    cubeApp *pThis = (cubeApp*)glfwGetWindowUserPointer(window);
    pThis->mouseClick(button, action, mods);
}

void cubeApp::mouseClick(i32 button, i32 action, i32 mods){

}

/* **************************************************************************************************** */

void cubeApp::onMouseMove(GLFWwindow* window, f64 x, f64 y){
    cubeApp *pThis = (cubeApp*)glfwGetWindowUserPointer(window);
    pThis->mouseMove(x, y);
}

void cubeApp::mouseMove(f64 x, f64 y){

}

/* **************************************************************************************************** */

void cubeApp::onMouseWheel(GLFWwindow* window, f64 xoffset, f64 yoffset){
    cubeApp *pThis = (cubeApp*)glfwGetWindowUserPointer(window);
    pThis->mouseWheel(xoffset, yoffset);
}

void cubeApp::mouseWheel(f64 xoffset, f64 yoffset){

}

/* **************************************************************************************************** */

void cubeApp::setVsync(i32 enable){
    info.flags.vsync = enable ? 1 : 0;
    glfwSwapInterval((i32)info.flags.vsync);
}

/* **************************************************************************************************** */

void cubeApp::getMousePosition(i32 *x, i32 *y){
    f64 dx, dy;
    glfwGetCursorPos(window, &dx, &dy);

    *x = (i32)(floor(dx));
    *y = (i32)(floor(dy));
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
    
    i32 error = glGetError();

    if(error != GL_NO_ERROR)
        errorAbort(error, message);
}

/* **************************************************************************************************** */

void cubeApp::update(){
    f64 deltaMove = 0.025;

    for(i32 i = 0; i < GLFW_KEY_LAST; i++){
        if(!pressed[i])
            continue;

        switch(i){
            case GLFW_KEY_A:
                modelMatrix = glm::rotate(
                    modelMatrix,
                    (f32)glfwGetTime(),
                    glm::vec3(1.0f, 0.0f, 0.0f)
                );
                break;

            case GLFW_KEY_D:
                modelMatrix = glm::rotate(
                    modelMatrix,
                    (f32)glfwGetTime(),
                    glm::vec3(0.0f, 0.0f, 1.0f)
                );
                break;

            case GLFW_KEY_W:
                modelMatrix = glm::rotate(
                    modelMatrix,
                    (f32)glfwGetTime(),
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
    currentTime = glfwGetTime();
}

/* **************************************************************************************************** */
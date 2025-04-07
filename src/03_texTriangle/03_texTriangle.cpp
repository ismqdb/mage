/* **************************************************************************************************** */

#include "./03_texTriangle.hpp"

/* **************************************************************************************************** */

i32 main(){
    texTriangle texTriangle{};

    texTriangle.gameLoop();
}

/* **************************************************************************************************** */

texTriangle::texTriangle() : app(){
    memset(this->pressed, 0, GLFW_KEY_LAST);

    glfwSetup();
    openglSetup();
}

texTriangle::~texTriangle() {
    openglTeardown();
    glfwTeardown();
}

/* **************************************************************************************************** */

void texTriangle::openglSetup(){
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexStorage2D(
        GL_TEXTURE_2D,
        8,
        GL_RGBA32F,
        256, 256
    );

    const i16 dataCount = 256;

    f32 *data = new f32[dataCount * dataCount * 4];

    generateTexture(data, dataCount, dataCount);

    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0, 0,
        dataCount, dataCount,
        GL_RGBA,
        GL_FLOAT,
        data
    );

    delete []data;

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
}

/* **************************************************************************************************** */

void texTriangle::render(){    
    GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, green);
    
    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

/* **************************************************************************************************** */

void texTriangle::openglTeardown(){
    glUseProgram(0);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, vao);
}

/* **************************************************************************************************** */

void texTriangle::gameLoop(){
    i32 running = 1;

    mage::shader shaders[] = {
        {GL_VERTEX_SHADER, "../shaders/03_texTriangle/03_texTriangle.vert"},
        {GL_FRAGMENT_SHADER, "../shaders/03_texTriangle/03_texTriangle.frag"},
        {GL_NONE, NULL}
    };

    program = mage::loadShader(shaders); 
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

void texTriangle::glfwSetup(){
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

void texTriangle::glfwTeardown(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

/* **************************************************************************************************** */

void texTriangle::onResize(GLFWwindow* window, i32 width, i32 height){
    texTriangle *pThis = (texTriangle*)glfwGetWindowUserPointer(window);
    pThis->resizeWindow(width, height);
}

void texTriangle::resizeWindow(i32 width, i32 height){
    glViewport(0, 0, width, height);
    aspectRatio = f32(width)/f32(height);
}

/* **************************************************************************************************** */

void texTriangle::onKey(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods){
    texTriangle *pThis = (texTriangle*)glfwGetWindowUserPointer(window);
    pThis->keyPress(key, scancode, action, mods);
}

void texTriangle::keyPress(i32 key, i32 scancode, i32 action, i32 mods){
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

void texTriangle::onMouseButton(GLFWwindow* window, i32 button, i32 action, i32 mods){
    texTriangle *pThis = (texTriangle*)glfwGetWindowUserPointer(window);
    pThis->mouseClick(button, action, mods);
}

void texTriangle::mouseClick(i32 button, i32 action, i32 mods){

}

/* **************************************************************************************************** */

void texTriangle::onMouseMove(GLFWwindow* window, f64 x, f64 y){
    texTriangle *pThis = (texTriangle*)glfwGetWindowUserPointer(window);
    pThis->mouseMove(x, y);
}

void texTriangle::mouseMove(f64 x, f64 y){

}

/* **************************************************************************************************** */

void texTriangle::onMouseWheel(GLFWwindow* window, f64 xoffset, f64 yoffset){
    texTriangle *pThis = (texTriangle*)glfwGetWindowUserPointer(window);
    pThis->mouseWheel(xoffset, yoffset);
}

void texTriangle::mouseWheel(f64 xoffset, f64 yoffset){

}

/* **************************************************************************************************** */

void texTriangle::setVsync(i32 enable){
    info.flags.vsync = enable ? 1 : 0;
    glfwSwapInterval((i32)info.flags.vsync);
}

/* **************************************************************************************************** */

void texTriangle::getMousePosition(i32 *x, i32 *y){
    f64 dx, dy;
    glfwGetCursorPos(window, &dx, &dy);

    *x = (i32)(floor(dx));
    *y = (i32)(floor(dy));
}

/* **************************************************************************************************** */

void GLAPIENTRY
texTriangle::MessageCallback(GLenum source,
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

void texTriangle::update(){
}

/* **************************************************************************************************** */

void texTriangle::generateTexture(f32 *data, i32 width, i32 height){
    i32 x, y;

    for (y = 0; y < height; y++)
        for (x = 0; x < width; x++)
            data[(y * width + x) * 4 + 0] = (f32)((x & y) & 0xFF) / 255.0f;
            data[(y * width + x) * 4 + 1] = (f32)((x | y) & 0xFF) / 255.0f;
            data[(y * width + x) * 4 + 2] = (f32)((x ^ y) & 0xFF) / 255.0f;
            data[(y * width + x) * 4 + 3] = 1.0f;
}

/* **************************************************************************************************** */
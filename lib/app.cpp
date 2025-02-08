/* **************************************************************************************************** */

#include "../headers/app.hpp"

/* **************************************************************************************************** */

void app::onResize(GLFWwindow* window, int w, int h){
    app *pThis = (app*)glfwGetWindowUserPointer(window);
    pThis->resizeWindow(w, h);
}

void app::resizeWindow(int x, int y){
    info.windowWidth = x;
    info.windowHeight = y;
}

/* **************************************************************************************************** */

void app::onKey(GLFWwindow* window, int key, int scancode, int action, int mods){
    app *pThis = (app*)glfwGetWindowUserPointer(window);
    pThis->keyPress(key, scancode, action, mods);
}

void app::keyPress(int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_LEFT){
        
    }

    if(key == GLFW_KEY_RIGHT){

    }
}

/* **************************************************************************************************** */

void app::onMouseButton(GLFWwindow* window, int button, int action, int mods){
    app *pThis = (app*)glfwGetWindowUserPointer(window);
    pThis->mouseClick(button, action, mods);
}

void app::mouseClick(int button, int action, int mods){

}

/* **************************************************************************************************** */

void app::onMouseMove(GLFWwindow* window, double x, double y){
    app *pThis = (app*)glfwGetWindowUserPointer(window);
    pThis->mouseMove(x, y);
}

void app::mouseMove(double x, double y){

}

/* **************************************************************************************************** */

void app::onMouseWheel(GLFWwindow* window, double xoffset, double yoffset){
    app *pThis = (app*)glfwGetWindowUserPointer(window);
    pThis->mouseWheel(xoffset, yoffset);
}

void app::mouseWheel(double xoffset, double yoffset){

}

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

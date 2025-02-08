/* **************************************************************************************************** */

#pragma once

/* **************************************************************************************************** */

#include "../glad/glad.h" // https://glad.dav1d.de/
#include <GLFW/glfw3.h>

/* **************************************************************************************************** */

#include "./loadShader.hpp"

/* **************************************************************************************************** */

#include <string>

#include <iostream>
#include <string>
#include <cmath> 

/* **************************************************************************************************** */

struct appInfo {
    std::string title;
    int windowWidth;
    int windowHeight;
    int majorVersion;
    int minorVersion;
    int samples;
    union {
        struct {
            unsigned int    fullscreen  : 1;
            unsigned int    vsync       : 1;
            unsigned int    cursor      : 1;
            unsigned int    stereo      : 1;
            unsigned int    debug       : 1;
            unsigned int    robust      : 1;
        };
        unsigned int        all;
    } flags;
};

/* **************************************************************************************************** */

class app {
    public:
        virtual void startup();
        virtual void shutdown();
        virtual void render();
        virtual void run();
        virtual void init();
        virtual void deinit();

        void onResize(GLFWwindow*, int, int);
        void onKey(GLFWwindow*, int, int, int, int);
        void onMouseButton(GLFWwindow*, int, int, int);
        void onMouseMove(GLFWwindow*, double, double);
        void onMouseWheel(GLFWwindow*, double, double);

        void setVsync(int);
        void getMousePosition(int*, int*);

    private:
        appInfo info;
        GLFWwindow *window;
};

/* **************************************************************************************************** */
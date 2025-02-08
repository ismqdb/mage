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
        virtual ~app();

        virtual void startup() = 0;
        virtual void shutdown() = 0;
        virtual void render() = 0;
        virtual void run() = 0;
        virtual void init() = 0;
        virtual void deinit() = 0;

        static void onResize(GLFWwindow*, int, int);
        virtual void resizeWindow(int, int);

        static void onKey(GLFWwindow*, int, int, int, int);
        virtual void keyPress(int, int, int, int);

        static void onMouseButton(GLFWwindow*, int, int, int);
        virtual void mouseClick(int, int, int);

        static void onMouseMove(GLFWwindow*, double, double);
        virtual void mouseMove(double, double);

        static void onMouseWheel(GLFWwindow*, double, double);
        virtual void mouseWheel(double, double);

        void setVsync(int);
        void getMousePosition(int*, int*);

    protected:
        appInfo info;
        GLFWwindow *window;
};

/* **************************************************************************************************** */
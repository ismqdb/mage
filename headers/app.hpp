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
        virtual ~app(){}

        virtual void startup() = 0;
        virtual void shutdown() = 0;
        virtual void render() = 0;
        virtual void run() = 0;
        virtual void init() = 0;
        virtual void deinit() = 0;
        virtual void update() = 0;

    protected:
        appInfo info;
        GLFWwindow *window;
};

/* **************************************************************************************************** */
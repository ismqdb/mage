/* **************************************************************************************************** */

#pragma once

/* **************************************************************************************************** */

#include "../glad/glad.h" // https://glad.dav1d.de/
#include <GLFW/glfw3.h>

/* **************************************************************************************************** */

#include "./loadShader.hpp"
#include "./types.hpp"

/* **************************************************************************************************** */

#include <string>

#include <iostream>
#include <string>
#include <cmath> 

/* **************************************************************************************************** */

namespace mage {
    struct appInfo {
        std::string title;
        i32 windowWidth;
        i32 windowHeight;
        i32 majorVersion;
        i32 minorVersion;
        i32 samples;
        union {
            struct {
                u32    fullscreen  : 1;
                u32    vsync       : 1;
                u32    cursor      : 1;
                u32    stereo      : 1;
                u32    debug       : 1;
                u32    robust      : 1;
            };
            u32        all;
        } flags;
    };
}

/* **************************************************************************************************** */

namespace mage {
    class app {
        public:
            virtual ~app(){}

            virtual void openglSetup() = 0;
            virtual void openglTeardown() = 0;
            virtual void render() = 0;
            virtual void gameLoop() = 0;
            virtual void glfwSetup() = 0;
            virtual void glfwTeardown() = 0;
            virtual void update() = 0;

        protected:
            appInfo info;
            GLFWwindow *window;
    };
}

/* **************************************************************************************************** */
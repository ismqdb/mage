/* **************************************************************************************************** */

#include "../../headers/app.hpp"
#include "../../headers/types.hpp"

#include <cstring>

/* **************************************************************************************************** */

class dotApp : public mage::app {
    public:
        dotApp();
        ~dotApp() override;

        void openglSetup() override;
        void openglTeardown() override;
        void render() override;
        void gameLoop() override;
        void glfwSetup() override;
        void glfwTeardown() override;
        void update() override;

        static void onResize(GLFWwindow*, i32, i32);
        virtual void resizeWindow(i32, i32);

        static void onKey(GLFWwindow*, i32, i32, i32, i32);
        virtual void keyPress(i32, i32, i32, i32);

        static void onMouseButton(GLFWwindow*, i32, i32, i32);
        virtual void mouseClick(i32, i32, i32);

        static void onMouseMove(GLFWwindow*, double, double);
        virtual void mouseMove(double, double);

        static void onMouseWheel(GLFWwindow*, double, double);
        virtual void mouseWheel(double, double);

        void setVsync(i32);
        void getMousePosition(i32*, i32*);

        static void GLAPIENTRY MessageCallback(GLenum,
            GLenum,
            GLuint,
            GLenum,
            GLsizei,
            const GLchar*,
            const void*);

    private:
        i32 numVAOs = 1;
        i32 numBuffers = 1;

        GLuint VAOs[1];
        GLuint buffers[1];

        GLuint numVertices = 0;
        GLfloat vertices[1][2];

        i32 pointSize = 5;

        bool pressed[GLFW_KEY_LAST];
};

/* *****************************************************************************************************/
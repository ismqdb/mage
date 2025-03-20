/* **************************************************************************************************** */

#include "../../headers/app.hpp"

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

        static void GLAPIENTRY MessageCallback(GLenum,
            GLenum,
            GLuint,
            GLenum,
            GLsizei,
            const GLchar*,
            const void*);

    private:
        int numVAOs = 1;
        int numBuffers = 1;

        GLuint VAOs[1];
        GLuint buffers[1];

        GLuint numVertices = 0;
        GLfloat vertices[1][2];

        int pointSize = 5;

        bool pressed[GLFW_KEY_LAST];
};

/* *****************************************************************************************************/
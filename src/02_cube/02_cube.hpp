/* **************************************************************************************************** */

#include "../../headers/app.hpp"

#include <cstring>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* **************************************************************************************************** */

class cubeApp : public mage::app {
    public:
        cubeApp();
        ~cubeApp() override;

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
        bool pressed[GLFW_KEY_LAST];
        
        float aspectRatio;
        GLuint program;

        GLuint vao;
        GLuint buffer;
        GLint mvLocation;
        GLint projLocation;
        glm::mat4 projMatrix;

        GLfloat vertexPositions[108] = {
            -0.25f,  0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f,  0.25f,

            -0.25f,  0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
             0.25f,  0.25f,  0.25f,

             0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f, -0.25f
        };


};

/* *****************************************************************************************************/
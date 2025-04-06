/* **************************************************************************************************** */

#include "../../headers/app.hpp"

#include <cstring>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* **************************************************************************************************** */

class triangleApp : public mage::app {
    public:
        triangleApp();
        ~triangleApp() override;

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
        bool pressed[GLFW_KEY_LAST];
        
        f32 aspectRatio;
        GLuint program;

        GLuint vao[1];
        GLuint vbo[1];
        GLuint ebo[1];

        GLint translationMatrixPosition;

        GLfloat vertexPositions[16] = {
            -0.9f, -0.4f,  0.0f, 1.0f,
            -0.7f, -0.4f,  0.0f, 1.0f,
            -0.9f,  0.4f,  0.0f, 1.0f,
        };

        GLfloat vertexColors[16] = {
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f
        };

        GLushort vertexIndices[3] = {
            0, 1, 2
        };

        GLfloat black[4] = {0.0f, 0.0f, 0.0f, 0.0f};

        glm::mat4 modelMatrix;
    
        glm::mat4 triangle_1;
        glm::mat4 triangle_2;
        glm::mat4 triangle_3;
        glm::mat4 triangle_4;
};

/* *****************************************************************************************************/
/* **************************************************************************************************** */

#include "../../headers/app.hpp"
#include "../../headers/errorMacros.hpp"

#include "../../headers/simpleArray.hpp"

/* **************************************************************************************************** */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* **************************************************************************************************** */

#include <cstring>
#include <array>

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

        static void onResize(GLFWwindow*, i32, i32);
        virtual void resizeWindow(i32, i32);

        static void onKey(GLFWwindow*, i32, i32, i32, i32);
        virtual void keyPress(i32, i32, i32, i32);

        static void onMouseButton(GLFWwindow*, i32, i32, i32);
        virtual void mouseClick(i32, i32, i32);

        static void onMouseMove(GLFWwindow*, f64, f64);
        virtual void mouseMove(f64, f64);

        static void onMouseWheel(GLFWwindow*, f64, f64);
        virtual void mouseWheel(f64, f64);

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
        void initPoints();

        bool pressed[GLFW_KEY_LAST];
        
        f32 aspectRatio;
        GLuint program;
        i32 fov = 45.0f;

        i32 currentTime;

        GLuint vao;
        GLuint positionBuffer;
        GLuint indexBuffer;

        GLint projectionMatrixLocation;
        GLint viewMatrixLocation;
        GLint modelMatrixLocation;
        
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 modelMatrix;

        GLushort vertexIndices[36] = {
            0, 1, 2,
            2, 1, 3,
            2, 3, 4,
            4, 3, 5,
            4, 5, 6,
            6, 5, 7,
            6, 7, 0,
            0, 7, 1,
            6, 0, 2,
            2, 4, 6,
            7, 5, 3,
            7, 3, 1
        };

        simpleArray<f32, 4> vertexPositions{50};
};

/* *****************************************************************************************************/
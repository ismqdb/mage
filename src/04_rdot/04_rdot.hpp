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

class rdot : public mage::app {
    public:
        rdot();
        ~rdot() override;

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
        void initIndices();

        bool pressed[GLFW_KEY_LAST];
        
        f32 aspectRatio;
        GLuint program;
        i32 fov = 45.0f;

        i32 currentTime;

        i32 circleRadius = 10;

        GLuint vao;
        GLuint positionBuffer;
        GLuint indexBuffer;

        GLint projectionMatrixLocation;
        GLint viewMatrixLocation;
        GLint modelMatrixLocation;
        
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 modelMatrix;

        simpleArray<f32, 4> vertexPositions{50};
        simpleArray<u32, 3> vertexIndices{50};
};

/* *****************************************************************************************************/
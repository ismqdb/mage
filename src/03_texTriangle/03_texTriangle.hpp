/* **************************************************************************************************** */

#include "../../headers/app.hpp"

#include <cstring>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* **************************************************************************************************** */

class texTriangle : public mage::app {
    public:
        texTriangle();
        ~texTriangle() override;

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
        void generateTexture(f32*, i32, i32);

        bool pressed[GLFW_KEY_LAST];
        
        f32 aspectRatio;
        GLuint program;

        GLuint vao[1];
        GLuint texture[1];
};

/* *****************************************************************************************************/
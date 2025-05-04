/* **************************************************************************************************** */

#include "../../headers/app.hpp"
#include "../../headers/errorMacros.hpp"

#include "../../headers/mageObject.hpp"

#include "../../headers/simpleArray.hpp"
#include "../../headers/vec.hpp"

#include "../../headers/circle.hpp"

/* **************************************************************************************************** */

#include "../../headers/oglHeaders.hpp"

/* **************************************************************************************************** */

#include <cstring>
#include <array>
#include <cmath>

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

        void addObject(mage::mageObject*);

    private:
        bool pressed[GLFW_KEY_LAST];
        
        f32 aspectRatio;
        GLuint program;
        i32 fov = 45.0f;

        i32 currentTime;

        GLint projectionMatrixLocation;
        GLint viewMatrixLocation;
        GLint modelMatrixLocation;
        
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 modelMatrix;

        mage::simpleArray<mage::mageObject*, sizeof(mage::mageObject)> objects{50};
};

/* *****************************************************************************************************/
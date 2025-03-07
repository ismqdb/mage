/* **************************************************************************************************** */

#include "../../headers/app.hpp"

#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* **************************************************************************************************** */

class dotApp : public app {
    public:
        dotApp();
        ~dotApp() override;

        void startup() override;
        void shutdown() override;
        void render() override;
        void run() override;
        void init() override;
        void deinit() override;
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
        const GLfloat vertexPositions[16] = {
            -1.0f, -1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 1.0f
        };
        
        const GLfloat vertexColors[16] = {
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f
        };
        
        const GLushort vertexIndices[16] = {
            0, 1, 2
        };

        bool pressed[GLFW_KEY_LAST];
        GLuint ebo, vbo, vao;
};

/* *****************************************************************************************************/
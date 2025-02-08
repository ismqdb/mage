/* **************************************************************************************************** */

#include "../../headers/app.hpp"

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
    private:
        const int triangles = 0;
        const int numVAOs = 1;

        const int arrayBuffer = 0;
        const int numBuffers = 1;
        const int vPosition = 0;

        GLuint VAOs[1];
        GLuint buffers[1];

        GLuint numVertices = 0;
};

/* **************************************************************************************************** */
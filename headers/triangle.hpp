/* **************************************************************************************************** */

#pragma once

/* **************************************************************************************************** */
#include <cassert>

/* **************************************************************************************************** */

#include "./app.hpp"

#include "./types.hpp"
#include "./simpleArray.hpp"
#include "./vec.hpp"

/* **************************************************************************************************** */

namespace mage {
    class triangle : public mage::mageObject {   
        public:
            triangle(){}
            triangle(mage::vec3, mage::vec3, mage::vec3);

            void prepareForRender() override;
            void render() override;
            void onInput() override;
            void setProgram(i32);
        
        private:;
            i32 m_program;

            simpleArray<mage::vec3, 12> vertexPositions{50};
            simpleArray<u32, 3> vertexIndices{50};
    };
}

/* **************************************************************************************************** */
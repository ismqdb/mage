/* **************************************************************************************************** */

#pragma once

/* **************************************************************************************************** */
#include <cassert>

/* **************************************************************************************************** */

#include "./app.hpp"

#include "./types.hpp"
#include "./vertexArray.hpp"
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

            mage::vertexArray<mage::vec3, 3> positionVectors{8};
            mage::vertexArray<u32, 3> indicesVectors{8};
    };
}

/* **************************************************************************************************** */
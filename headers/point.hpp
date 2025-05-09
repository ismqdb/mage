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
    class point : public mage::mageObject {   
        public:
            point(){}
            point(mage::vec3);

            void prepareForRender() override;
            void render() override;
            void onInput() override;
            void setProgram(i32);
        
        private:
            i32 m_program;
            mage::vec3 m_position;

            mage::vertexArray<3> m_vertexArray;
    };
}

/* **************************************************************************************************** */
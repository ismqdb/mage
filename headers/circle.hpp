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
    class circle : public mage::mageObject {   
        public:
            circle(){}
            circle(mage::vec3, f32, u32);

            void prepareForRender() override;
            void render() override;
            void onInput() override;
            void setProgram(i32);
        
        private:
            void initPoints();
            void initIndices();

            mage::vec3 m_position;

            f32 m_radius;
            u32 m_noOfTriangles;
            f64 m_arcLen;
            i32 m_program;

            simpleArray<f32, 4> vertexPositions{50};
            simpleArray<u32, 3> vertexIndices{50};
    };
}

/* **************************************************************************************************** */
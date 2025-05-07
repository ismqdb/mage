/* **************************************************************************************************** */

#pragma once

/* **************************************************************************************************** */

#include "./types.hpp"
#include "./mageObject.hpp"
#include "./simpleArray.hpp"
#include "./vec.hpp"

/* **************************************************************************************************** */

#include <cassert>
#include <cstdlib>

/* **************************************************************************************************** */

namespace mage {
    template<u8 t_stride>
        class vertexArray {
            public:
                vertexArray();
                ~vertexArray();

                void insertIndice(u32, u32, u32);
                void insertPoint(mage::vec3);

                u8 stride();

                u32* vbo();
                u32* vao();
                u32* ebo();

                u64 vertexSizeof();
                u64 indiceSizeof();

                f64 *vertices_raw();
                u32 *indices_raw();

                u32 vertexCount();
                u32 indiceCount();

            private:
                mage::simpleArray<f64> points{8};
                mage::simpleArray<u32> indices{8};
                
                u8 m_stride = t_stride;
                
                u32 *m_vao;
                u32 *m_vbo;
                u32 *m_ebo;
        };
}

/* **************************************************************************************************** */

template class mage::vertexArray<4>;
template class mage::vertexArray<3>;

/* **************************************************************************************************** */
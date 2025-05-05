/* **************************************************************************************************** */

#pragma once

/* **************************************************************************************************** */

#include "./types.hpp"
#include "./mageObject.hpp"
#include "./vec.hpp"

/* **************************************************************************************************** */

#include <cassert>
#include <cstdlib>

/* **************************************************************************************************** */

namespace mage {
    template<typename Type, u8 t_stride>
        class vertexArray {
            public:
                vertexArray(u32);
                ~vertexArray();

                void insert(Type);
                void insertIndice(Type, Type, Type);
                void insertPoint(Type, Type, Type, Type);

                Type* raw();
                u64 size();
                u64 size_of();
                u8 stride();

                u32* buf();
                u32* vao();

                Type* operator[](i32);

            private:
                void reserve();

                Type *m_data = nullptr;
                u64 m_size = 0;
                u64 m_capacity = 0;
                u64 m_currentIdx;
                u64 m_sizeof;
                
                u8 m_stride = t_stride;
                
                u32 *m_buffer;
                u32 *m_vao;
        };
}

/* **************************************************************************************************** */

template class mage::vertexArray<i32, 4>;
template class mage::vertexArray<u32, 3>;
template class mage::vertexArray<f32, 4>;

template class mage::vertexArray<mage::vec3, 3>;
template class mage::vertexArray<mage::mageObject*, sizeof(mage::mageObject*)>;

/* **************************************************************************************************** */
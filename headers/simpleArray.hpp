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
        class simpleArray {
            public:
                simpleArray(u32);
                ~simpleArray();

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

template class mage::simpleArray<i32, 4>;
template class mage::simpleArray<u32, 3>;
template class mage::simpleArray<f32, 4>;

template class mage::simpleArray<mage::vec3, 3>;
template class mage::simpleArray<mage::mageObject*, sizeof(mage::mageObject*)>;

/* **************************************************************************************************** */
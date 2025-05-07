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
    template<typename Type>
        class simpleArray {
            public:
                simpleArray(u32);
                ~simpleArray();

                void insert(Type);

                u64 size();

                Type* operator[](i32);
                Type* raw();
                u64 size_of();

            private:
                void reserve();

                Type *m_data = nullptr;
                u64 m_size = 0;
                u64 m_capacity = 0;
                u64 m_currentIdx;
                u64 m_sizeof;
        };
}

/* **************************************************************************************************** */

template class mage::simpleArray<i32>;
template class mage::simpleArray<u32>;
template class mage::simpleArray<f32>;
template class mage::simpleArray<f64>;

template class mage::simpleArray<mage::vec3>;
template class mage::simpleArray<mage::mageObject*>;

/* **************************************************************************************************** */
/* **************************************************************************************************** */

#include "../headers/simpleArray.hpp"

/* **************************************************************************************************** */

template<typename Type>
    mage::simpleArray<Type>::simpleArray(u32 startSize){
        assert(startSize > 0);

        m_data = (Type*)malloc(startSize * sizeof(Type));
        m_capacity = startSize;
        m_currentIdx = 0;
        m_sizeof = 0;
    }

template<typename Type>
    mage::simpleArray<Type>::~simpleArray(){
        free(m_data);
        m_size = 0;
        m_currentIdx = 0;
        m_sizeof = 0;
    }

/* **************************************************************************************************** */

template<typename Type>
    void mage::simpleArray<Type>::insert(Type newValue){
        if(m_size == m_capacity)
            reserve();

        m_data[m_currentIdx++] = newValue;
        m_size++;
        m_sizeof += sizeof(Type);
    }

/* **************************************************************************************************** */

template<typename Type>
    void mage::simpleArray<Type>::reserve(){
        m_data = (Type*)realloc(m_data, (m_capacity*2) * sizeof(Type));
        m_capacity *= 2;
    }

/* **************************************************************************************************** */

template<typename Type>
    u64 mage::simpleArray<Type>::size(){
        return m_size;
    }

/* **************************************************************************************************** */

template<typename Type>
    Type* mage::simpleArray<Type>::operator[](i32 i){
        if(i > (size() - 1))
            throw;

        return m_data + i;
    } 

/* **************************************************************************************************** */

template<typename Type>
    Type* mage::simpleArray<Type>::raw(){
        return m_data;
    }

/* **************************************************************************************************** */

template<typename Type>
    u64 mage::simpleArray<Type>::size_of(){
        return m_sizeof;
    }

/* **************************************************************************************************** */
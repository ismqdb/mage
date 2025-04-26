/* **************************************************************************************************** */

#include "../headers/simpleArray.hpp"

/* **************************************************************************************************** */

template<typename T>
    simpleArray<T>::simpleArray(u32 startSize){
        assert(startSize > 0);

        m_data = (T*)malloc(startSize * sizeof(T));
        m_capacity = startSize;
        m_currentIdx = 0;
        m_sizeof = 0;
    }

template<typename T>
    simpleArray<T>::~simpleArray(){
        free(m_data);
        m_size = 0;
        m_currentIdx = 0;
        m_sizeof = 0;
    }

/* **************************************************************************************************** */

template<typename T>
    void simpleArray<T>::insert(T newValue){
        if(m_size == m_capacity)
            reserve();

        m_data[m_currentIdx++] = newValue;
        m_size++;
        m_sizeof += sizeof(T);
    }

template<typename T>
    void simpleArray<T>::insertPoint(T x, T y, T z, T w){
        insert(x);
        insert(y);
        insert(z);
        insert(w);
    }

/* **************************************************************************************************** */

template<typename T>
    void simpleArray<T>::reserve(){
        m_data = (T*)realloc(m_data, (m_capacity*2) * sizeof(T));
        m_capacity *= 2;
    }

/* **************************************************************************************************** */

template<typename T>
    T* simpleArray<T>::raw(){
        return m_data;
    }

/* **************************************************************************************************** */

template<typename T>
    u64 simpleArray<T>::size(){
        return m_size;
    }

template<typename T>
    u64 simpleArray<T>::size_of(){
        return m_sizeof;
    }

/* **************************************************************************************************** */
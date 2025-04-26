/* **************************************************************************************************** */

#include "../headers/simpleArray.hpp"

/* **************************************************************************************************** */

template<typename T>
    simpleArray<T>::simpleArray(u32 startSize){
        assert(startSize > 0);

        this->data = (T*)malloc(startSize * sizeof(T));
        this->capacity = startSize;
        this->currentIdx = 0;
    }

template<typename T>
    simpleArray<T>::~simpleArray(){
        free(this->data);
        m_size = 0;
        currentIdx = 0;
    }

/* **************************************************************************************************** */

template<typename T>
    void simpleArray<T>::insert(T newValue){
        if(m_size == capacity)
            reserve();

        data[currentIdx++] = newValue;
        m_size++;
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
        this->data = (T*)realloc(this->data, (this->capacity*2) * sizeof(T));
        this->capacity *= 2;
    }

/* **************************************************************************************************** */

template<typename T>
    T* simpleArray<T>::raw(){
        return data;
    }

/* **************************************************************************************************** */

template<typename T>
    u64 simpleArray<T>::size(){
        return m_size;
    }

/* **************************************************************************************************** */
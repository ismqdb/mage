/* **************************************************************************************************** */

#include "../headers/simpleArray.hpp"

/* **************************************************************************************************** */

template<typename Type, u8 t_stride>
    simpleArray<Type, t_stride>::simpleArray(u32 startSize){
        assert(startSize > 0);

        m_data = (Type*)malloc(startSize * sizeof(Type));
        m_capacity = startSize;
        m_currentIdx = 0;
        m_sizeof = 0;
    }

template<typename Type, u8 t_stride>
    simpleArray<Type, t_stride>::~simpleArray(){
        free(m_data);
        m_size = 0;
        m_currentIdx = 0;
        m_sizeof = 0;
    }

/* **************************************************************************************************** */

template<typename Type, u8 t_stride>
    void simpleArray<Type, t_stride>::insert(Type newValue){
        if(m_size == m_capacity)
            reserve();

        m_data[m_currentIdx++] = newValue;
        m_size++;
        m_sizeof += sizeof(Type);
    }

template<typename Type, u8 t_stride>
    void simpleArray<Type, t_stride>::insertIndice(Type a, Type b, Type c){
        insert(a);
        insert(b);
        insert(c);
    }

template<typename Type, u8 t_stride>
    void simpleArray<Type, t_stride>::insertPoint(Type x, Type y, Type z, Type w){
        insert(x);
        insert(y);
        insert(z);
        insert(w);
    }

/* **************************************************************************************************** */

template<typename Type, u8 t_stride>
    void simpleArray<Type, t_stride>::reserve(){
        m_data = (Type*)realloc(m_data, (m_capacity*2) * sizeof(Type));
        m_capacity *= 2;
    }

/* **************************************************************************************************** */

template<typename Type, u8 t_stride>
    Type* simpleArray<Type, t_stride>::raw(){
        return m_data;
    }

/* **************************************************************************************************** */

template<typename Type, u8 t_stride>
    u64 simpleArray<Type, t_stride>::size(){
        return m_size;
    }

template<typename Type, u8 t_stride>
    u64 simpleArray<Type, t_stride>::size_of(){
        return m_sizeof;
    }

/* **************************************************************************************************** */

template<typename Type, u8 t_stride>
    u8 simpleArray<Type, t_stride>::stride(){
        return m_stride;
    }

/* **************************************************************************************************** */
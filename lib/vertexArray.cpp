/* **************************************************************************************************** */

#include "../headers/vertexArray.hpp"

/* **************************************************************************************************** */

template<u8 t_stride>
    mage::vertexArray<t_stride>::vertexArray(){
        m_vboSizeof = 0;
        m_eboSizeof = 0;

        m_vbo = new u32{};
        m_vao = new u32{};
        m_ebo = new u32{};
    }

template<u8 t_stride>
    mage::vertexArray<t_stride>::~vertexArray(){
        delete m_ebo;
        delete m_vbo;
        delete m_vao;
    }

/* **************************************************************************************************** */

template<u8 t_stride>
    void mage::vertexArray<t_stride>::insertIndice(u32 a, u32 b, u32 c){
        indices.insert(a);
        indices.insert(b);
        indices.insert(c);
        m_eboSizeof += (3 * sizeof(u32));
    }

template<u8 t_stride>
    void mage::vertexArray<t_stride>::insertPoint(mage::vec3 point){
        points.insert(point.x);
        points.insert(point.y);
        points.insert(point.z);
        m_vboSizeof += (3 * sizeof(f64));
    }

/* **************************************************************************************************** */

template<u8 t_stride>
    u8 mage::vertexArray<t_stride>::stride(){
        return m_stride;
    }

/* **************************************************************************************************** */

template<u8 t_stride>
    u32* mage::vertexArray<t_stride>::vbo(){
        return m_vbo;
    }

/* **************************************************************************************************** */

template<u8 t_stride>
    u32* mage::vertexArray<t_stride>::vao(){
        return m_vao;
    }

/* **************************************************************************************************** */

template<u8 t_stride>
    u32* mage::vertexArray<t_stride>::ebo(){
        return m_ebo;
    }

/* **************************************************************************************************** */

template<u8 t_stride>
    u64 mage::vertexArray<t_stride>::vertexSizeof(){
        return m_vboSizeof;
    }

/* **************************************************************************************************** */

template<u8 t_stride>
    u64 mage::vertexArray<t_stride>::indiceSizeof(){
        return m_eboSizeof;
    }

/* **************************************************************************************************** */

template<u8 t_stride>
    f64* mage::vertexArray<t_stride>::vertices_raw(){
        return points.raw();
    }

/* **************************************************************************************************** */

template<u8 t_stride>
    u32* mage::vertexArray<t_stride>::indices_raw(){
        return indices.raw();
    }

/* **************************************************************************************************** */

template<u8 t_stride>
    u32 mage::vertexArray<t_stride>::vertexCount(){
        return points.size();
    }

/* **************************************************************************************************** */

template<u8 t_stride>
    u32 mage::vertexArray<t_stride>::indiceCount(){
        return indices.size();
    }

/* **************************************************************************************************** */
/* **************************************************************************************************** */

#include "../headers/point.hpp"

/* **************************************************************************************************** */

mage::point::point(mage::vec3 a){
    m_vertexArray.insertPoint(a);
    m_vertexArray.insertIndice(0);
}

/* **************************************************************************************************** */

void mage::point::prepareForRender(){
    glGenVertexArrays(1, m_vertexArray.vao());
    glBindVertexArray(*m_vertexArray.vao());

    glGenBuffers(1, m_vertexArray.vbo());
    glBindBuffer(GL_ARRAY_BUFFER, *m_vertexArray.vbo());
    glBufferData(GL_ARRAY_BUFFER, m_vertexArray.vertexSizeof(), 
        m_vertexArray.vertices_raw(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, m_vertexArray.stride(), GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, m_vertexArray.ebo());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_vertexArray.ebo());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexArray.indiceSizeof(), 
        m_vertexArray.indices_raw(), GL_STATIC_DRAW);
}

/* **************************************************************************************************** */

void mage::point::render(){
    prepareForRender();
    glDrawElements(GL_POINTS, m_vertexArray.indiceCount(), GL_UNSIGNED_INT, 0);
}

/* **************************************************************************************************** */

void mage::point::onInput(){

}

/* **************************************************************************************************** */

void mage::point::setProgram(i32 program){
    m_program = program;
}

/* **************************************************************************************************** */
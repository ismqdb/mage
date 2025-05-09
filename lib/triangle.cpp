/* **************************************************************************************************** */

#include "../headers/triangle.hpp"

/* **************************************************************************************************** */

mage::triangle::triangle(mage::vec3 a, mage::vec3 b, mage::vec3 c){
    m_vertexArray.insertPoint(a);
    m_vertexArray.insertPoint(b);
    m_vertexArray.insertPoint(c);

    m_vertexArray.insertTriIndices(0, 1, 2);
}

/* **************************************************************************************************** */

void mage::triangle::prepareForRender(){
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

void mage::triangle::render(){
    prepareForRender();
    glDrawElements(GL_POINTS, m_vertexArray.indiceCount(), GL_UNSIGNED_INT, 0);
}

/* **************************************************************************************************** */

void mage::triangle::onInput(){

}

/* **************************************************************************************************** */

void mage::triangle::setProgram(i32 program){
    m_program = program;
}

/* **************************************************************************************************** */
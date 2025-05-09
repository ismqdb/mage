/* **************************************************************************************************** */

#include "../headers/circle.hpp"

/* **************************************************************************************************** */

mage::circle::circle(mage::vec3 position, f32 radius, u32 noOfTri){
    assert(radius > 0);
    assert(noOfTri > 0);

    m_position = position;
    m_radius = radius;
    m_noOfTriangles = noOfTri;
    m_arcLen = 360.0/m_noOfTriangles;

    initPoints();
    initIndices();
}

/* **************************************************************************************************** */

void mage::circle::initPoints(){
    f64 angle = 0.0;
    f64 angleRad;

    m_vertexArray.insertPoint(mage::vec3{.x = m_position.x, .y = m_position.y, .z = 0.0});

    for(int i = 0; i < m_noOfTriangles*2; i++){
        angleRad = (angle * M_PI) / 360;

        f64 x = m_position.x + m_radius * cos(angleRad);
        f64 y = m_position.y + m_radius * sin(angleRad);

        m_vertexArray.insertPoint(mage::vec3{.x = x, .y = y, .z = 0.0f});

        angle += m_arcLen;
    }
}

/* **************************************************************************************************** */

void mage::circle::initIndices(){
    int i = 0;
    
    for(; i < m_noOfTriangles*2; i++){
        m_vertexArray.insertTriIndices(0, i, i+1);
    }

    m_vertexArray.insertTriIndices(0, i, 1);
}

/* **************************************************************************************************** */

void mage::circle::prepareForRender(){
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

void mage::circle::render(){
    prepareForRender();
    glDrawElements(GL_TRIANGLES, m_vertexArray.indiceCount(), GL_UNSIGNED_INT, 0);
}

/* **************************************************************************************************** */

void mage::circle::onInput(){

}

/* **************************************************************************************************** */

void mage::circle::setProgram(i32 program){
    m_program = program;
}

/* **************************************************************************************************** */
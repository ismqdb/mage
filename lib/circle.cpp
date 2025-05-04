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

    vertexPositions.insertPoint(m_position.x, m_position.y, 0.0, 1.0);

    for(int i = 0; i < m_noOfTriangles*2; i++){
        angleRad = (angle * M_PI) / 360;

        f64 x = m_position.x + m_radius * cos(angleRad);
        f64 y = m_position.y + m_radius * sin(angleRad);

        vertexPositions.insertPoint(x, y, 0.0f, 1.0f);

        angle += m_arcLen;
    }
}

/* **************************************************************************************************** */

void mage::circle::initIndices(){
    int i = 0;
    
    for(; i < m_noOfTriangles*2; i++){
        vertexIndices.insertIndice(0, i, i+1);
    }

    vertexIndices.insertIndice(0, i, 1);
}

/* **************************************************************************************************** */

void mage::circle::prepareForRender(){
    glGenVertexArrays(1, vertexPositions.vao());
    glBindVertexArray(*vertexPositions.vao());

    glGenBuffers(1, vertexPositions.buf());
    glBindBuffer(GL_ARRAY_BUFFER, *vertexPositions.buf());
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size_of(), 
        vertexPositions.raw(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, vertexPositions.stride(), GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, vertexIndices.buf());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *vertexIndices.buf());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size_of(), 
        vertexIndices.raw(), GL_STATIC_DRAW);
}

/* **************************************************************************************************** */

void mage::circle::render(){
    prepareForRender();
    glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, 0);
}

/* **************************************************************************************************** */

void mage::circle::onInput(){

}

/* **************************************************************************************************** */

void mage::circle::setProgram(i32 program){
    m_program = program;
}

/* **************************************************************************************************** */
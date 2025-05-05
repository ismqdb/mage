/* **************************************************************************************************** */

#include "../headers/triangle.hpp"

/* **************************************************************************************************** */

mage::triangle::triangle(mage::vec3 a, mage::vec3 b, mage::vec3 c){

}

/* **************************************************************************************************** */

void mage::triangle::prepareForRender(){
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

void mage::triangle::render(){
    prepareForRender();
    glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, 0);
}

/* **************************************************************************************************** */

void mage::triangle::onInput(){

}

/* **************************************************************************************************** */

void mage::triangle::setProgram(i32 program){
    m_program = program;
}

/* **************************************************************************************************** */
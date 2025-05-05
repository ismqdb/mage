/* **************************************************************************************************** */

#include "../headers/triangle.hpp"

/* **************************************************************************************************** */

mage::triangle::triangle(mage::vec3 a, mage::vec3 b, mage::vec3 c){
    positionVectors.insert(a);
    positionVectors.insert(b);
    positionVectors.insert(c);
}

/* **************************************************************************************************** */

void mage::triangle::prepareForRender(){
    glGenVertexArrays(1, positionVectors.vao());
    glBindVertexArray(*positionVectors.vao());

    glGenBuffers(1, positionVectors.buf());
    glBindBuffer(GL_ARRAY_BUFFER, *positionVectors.buf());
    glBufferData(GL_ARRAY_BUFFER, positionVectors.size_of(), 
        positionVectors.raw(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, positionVectors.stride(), GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, indicesVectors.buf());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indicesVectors.buf());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesVectors.size_of(), 
        indicesVectors.raw(), GL_STATIC_DRAW);
}

/* **************************************************************************************************** */

void mage::triangle::render(){
    prepareForRender();
    glDrawElements(GL_TRIANGLES, indicesVectors.size(), GL_UNSIGNED_INT, 0);
}

/* **************************************************************************************************** */

void mage::triangle::onInput(){

}

/* **************************************************************************************************** */

void mage::triangle::setProgram(i32 program){
    m_program = program;
}

/* **************************************************************************************************** */
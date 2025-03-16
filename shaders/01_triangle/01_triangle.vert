#version 450

uniform mat4 translationMatrix;

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 inColor;

void main(void){
    inColor = color;
    gl_Position = (translationMatrix * position);
}
#version 450 core

in vec4 inColor;

layout (location = 0) out vec4 color;

void main(void){
    color = inColor;
}
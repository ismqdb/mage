#version 450

layout (location = 0) in vec4 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(void){
    gl_Position = projection * view * model * position;
}
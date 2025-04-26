#version 450

in vec4 position;

out vec4 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(void){
    gl_Position = projection * view * model * position;
    color = position * 2.0f + vec4(0.5, 0.5, 0.5, 0.0);
}
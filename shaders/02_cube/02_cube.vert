#version 450

in vec4 position;

out VS_OUT {
    vec4 color;
} vs_out;

uniform mat4 projection;
uniform mat4 view;

void main(void){
    gl_Position = view * position;
    vs_out.color = position * 2.0f + vec4(0.5, 0.5, 0.5, 0.0);
}
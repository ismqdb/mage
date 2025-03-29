#version 450

in vec3 position;

out VS_OUT {
    vec4 color;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(void){
    gl_Position = projection * view * model * vec4(position, 1.0f);
    vs_out.color = vec4(position, 1.0) * 2.0f + vec4(0.5, 0.5, 0.5, 0.0);
}
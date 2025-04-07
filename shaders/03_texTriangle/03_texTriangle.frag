#version 450 core

uniform sampler2D sam;

out vec4 color;

void main(void){
    color = texture(sam, gl_FragCoord.xy / textureSize(sam, 0));
}
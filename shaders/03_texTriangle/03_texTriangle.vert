#version 450

out vec4 inColor;

void main(void){
    const vec4 vertices[] = vec4[3](
        vec4( 0.75, -0.75, 0.5, 1.0),               
        vec4(-0.75, -0.75, 0.5, 1.0),              
        vec4( 0.75,  0.75, 0.5, 1.0)
    );

    gl_Position = vertices[gl_VertexID];
}
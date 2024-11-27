/* **************************************************************************************************** */

#include "../headers/helper_funcs.h"

/* **************************************************************************************************** */

void check_shader_compilation(int *fs){
    GLuint status;

    glGetShaderiv(*fs, GL_COMPILE_STATUS, &status);

    if(status == GL_FALSE){
        GLint maxLength = 0;
        glGetShaderiv(*fs, GL_INFO_LOG_LENGTH, &maxLength);

        char *error_log;
        glGetShaderInfoLog(*fs, maxLength, &maxLength, error_log);

        glDeleteShader(*fs); // Don't leak the shader.

        printf("Shader error -> %s.\n", error_log);
        exit(1);
    }
}

/* **************************************************************************************************** */

const char* read_shader_from_file(char *path){
    FILE *fp;
    fp = fopen(path, "r");

    int allocated_size = 1000;

    if(fp == NULL)
        return NULL;

    char *ret = (char*)malloc(allocated_size*sizeof(char));
    char c;

    int i = 0;

    while((c = getc(fp)) != EOF){
        *(ret+i++) = c;

        if(i == allocated_size)
            ret = realloc(ret, (allocated_size+1000)*sizeof(char));
    }

    ret[i] = '\0';

    return (const char*)ret;
}

/* **************************************************************************************************** */
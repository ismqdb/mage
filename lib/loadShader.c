/* **************************************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

/* **************************************************************************************************** */

#include "../glad/glad.h"
#include "../headers/loadShader.h"

/* **************************************************************************************************** */

#define _DEBUG

/* **************************************************************************************************** */

static const GLchar* readShader(const char* path){
    #ifdef WIN32
        FILE* infile;
        fopen_s(&infile, path, "rb");
    #else
        FILE* infile = fopen(path, "rb");
    #endif // WIN32

    if (!infile) {
        #ifdef _DEBUG
            fprintf(stderr, "Unable to open file %s.\n", path);
        #endif /* DEBUG */
        return NULL;
    }

    fseek(infile, 0, SEEK_END);
    int len = ftell(infile);
    fseek(infile, 0, SEEK_SET);

    GLchar* source = (GLchar*)malloc(sizeof(GLchar)*(len+1));

    fread(source, 1, len, infile);
    fclose(infile);

    source[len] = 0;

    return (const GLchar*)(source);
}

/* **************************************************************************************************** */

GLuint loadShader(struct shader* shaders){
    if (shaders == NULL){ 
        return 0; 
    }

    GLuint program = glCreateProgram();
    struct shader* entry = shaders;

    while (entry->type != GL_NONE) {
        GLuint shader = glCreateShader(entry->type);

        entry->name = shader;

        const GLchar* source = readShader(entry->path);

        if (source == NULL) {
            for (entry = shaders; entry->type != GL_NONE; ++entry) {
                glDeleteShader(entry->name);
                entry->name = 0;
            }
            return 0;
        }

        glShaderSource(shader, 1, &source, NULL);
        free((void*)source);

        glCompileShader(shader);

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled) {
            #ifdef _DEBUG
                GLsizei len;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

                GLchar* log[len+1];
                glGetShaderInfoLog(shader, len, &len, *log);
                fprintf(stderr, "Shader compilation failed: %s.\n", log);
            #endif

            return 0;
        }

        glAttachShader(program, shader);
        ++entry;
    }

    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked) {
        #ifdef _DEBUG
            GLsizei len;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

            GLchar* log[len+1];
            glGetProgramInfoLog(program, len, &len, *log);
            fprintf(stderr, "Shader linking failed: %s.\n", log);
        #endif

        for (entry = shaders; entry->type != GL_NONE; ++entry) {
            glDeleteShader(entry->name);
            entry->name = 0;
        }
        
        return 0;
    }

    return program;
}

/* **************************************************************************************************** */
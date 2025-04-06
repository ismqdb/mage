/* **************************************************************************************************** */

#include <iostream>

/* **************************************************************************************************** */

#include "../glad/glad.h"
#include "../headers/loadShader.hpp"

/* **************************************************************************************************** */

#define _DEBUG

/* **************************************************************************************************** */

static const GLchar* mage::readShader(const char* path){
    #ifdef WIN32
        FILE* infile;
        fopen_s(&infile, path, "rb");
    #else
        FILE* infile = fopen(path, "rb");
    #endif // WIN32

    if (!infile) {
        #ifdef _DEBUG
            std::cerr << "Unable to open file '" << path << "'" << std::endl;
        #endif /* DEBUG */
            return NULL;
    }

    fseek(infile, 0, SEEK_END);
    i32 len = ftell(infile);
    fseek(infile, 0, SEEK_SET);

    GLchar* source = new GLchar[len+1];

    fread(source, 1, len, infile);
    fclose(infile);

    source[len] = 0;

    return const_cast<const GLchar*>(source);
}

/* **************************************************************************************************** */

GLuint mage::loadShader(mage::shader* shaders){
    if (shaders == NULL) { 
        return 0; 
    }

    GLuint program = glCreateProgram();

    mage::shader* entry = shaders;
    while (entry->type != GL_NONE) {
        GLuint shader = glCreateShader(entry->type);

        entry->name = shader;

        const GLchar* source = mage::readShader(entry->path);
        if (source == NULL) {
            for (entry = shaders; entry->type != GL_NONE; ++entry) {
                glDeleteShader(entry->name);
                entry->name = 0;
            }

            return 0;
        }

        glShaderSource(shader, 1, &source, NULL);
        delete [] source;

        glCompileShader(shader);

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled) {
            #ifdef _DEBUG
                GLsizei len;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

                GLchar* log = new GLchar[len+1];
                glGetShaderInfoLog(shader, len, &len, log);
                std::cerr << "Shader compilation failed: " << log << std::endl;
                delete [] log;
            #endif /* DEBUG */

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

            GLchar* log = new GLchar[len+1];
            glGetProgramInfoLog(program, len, &len, log);
            std::cerr << "Shader linking failed: " << log << std::endl;
            delete [] log;
        #endif /* DEBUG */

        for (entry = shaders; entry->type != GL_NONE; ++entry) {
            glDeleteShader(entry->name);
            entry->name = 0;
        }
        
        return 0;
    }

    return program;
}

/* **************************************************************************************************** */
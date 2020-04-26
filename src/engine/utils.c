#include "utils.h"

void GLClearError(){
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line){
    GLenum error = glGetError();
    if (error != GL_NO_ERROR){
        printf("[OpenGL Error] (%u): %s linea: %d\nFile: %s", error, function, line, file);
        return false;
    }
    return true;
}

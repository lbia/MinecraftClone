#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include "vertexBuffer.h"
#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

typedef struct{

    VertexBuffer *vb;
    VertexArray *va;
    IndexBuffer *ib;
    Shader *shader;

} Program;

#endif // PROGRAM_H_INCLUDED

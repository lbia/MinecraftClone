#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "vertexBuffer.h"

typedef struct{

    unsigned int type;
    unsigned int count;
    unsigned char normalized;

} VertexBufferElement;

typedef struct{

    unsigned int numberElements;
    VertexBufferElement *m_Elements;
    unsigned int m_Stride;

} VertexBufferLayout;

typedef struct{

    unsigned int m_RendererID;

} VertexArray;

void initializeVertexArray(VertexArray *va);

void destroyVertexArray(VertexArray *va);

void bindVertexArray(VertexArray *va);

void unbindVertexArray(VertexArray *va);

void addBufferToVertexArray(VertexArray *va, const VertexBuffer *vb, const VertexBufferLayout *layout);

void initializeVertexBufferLayout(VertexBufferLayout *layout);

void destroyVertexBufferLayout(VertexBufferLayout *layout);

void pushElementToVertexBufferLayout(VertexBufferLayout *layout, unsigned int _type, unsigned int _count, char _normalized);

unsigned int getSizeOfType(unsigned int type);

#endif // VERTEXARRAY_H

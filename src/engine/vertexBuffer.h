#ifndef VERTEXBUFFER_H_INCLUDED
#define VERTEXBUFFER_H_INCLUDED

#include "stdbool.h"

typedef struct{
    unsigned int m_RendererID;

} VertexBuffer;

void initializeVertexBuffer(VertexBuffer *buffer);

void destroyVertexBuffer(VertexBuffer *buffer);

void sendDataVertexBuffer(VertexBuffer *buffer, const void *data, unsigned int size, bool dynamic);

void bindVertexBuffer(VertexBuffer *buffer);

void unbindVertexBuffer(VertexBuffer *buffer);

#endif // VERTEXBUFFER_H_INCLUDED

#ifndef INDEXBUFFER_H_INCLUDED
#define INDEXBUFFER_H_INCLUDED

#include "stdbool.h"

typedef struct{

    unsigned int m_RendererID;

} IndexBuffer;

void initializeIndexBuffer(IndexBuffer *buffer);

void destroyIndexBuffer(IndexBuffer *buffer);

void sendDataIndexBuffer(IndexBuffer *buffer, const unsigned int *data, unsigned int count, bool dynamic);

void bindIndexBuffer(IndexBuffer *buffer);

void unbindIndexBuffer(IndexBuffer *buffer);

#endif // INDEXBUFFER_H_INCLUDED

#include "indexBuffer.h"
#include "utils.h"

void initializeIndexBuffer(IndexBuffer *buffer){
    GLCall(glGenBuffers(1, &(buffer->m_RendererID)));
}

void sendDataIndexBuffer(IndexBuffer *buffer, const unsigned int *data, unsigned int size, bool dynamic){
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->m_RendererID));
    if (dynamic){
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    } else {
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }
}

void destroyIndexBuffer(IndexBuffer *buffer){
    GLCall(glDeleteBuffers(1, &(buffer->m_RendererID)));
}

void bindIndexBuffer(IndexBuffer *buffer){
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->m_RendererID));
}

void unbindIndexBuffer(IndexBuffer *buffer){
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

#include "vertexBuffer.h"

#include "utils.h"

void initializeVertexBuffer(VertexBuffer *buffer){
    GLCall(glGenBuffers(1, &(buffer->m_RendererID)));
}

void sendDataVertexBuffer(VertexBuffer *buffer, const void *data, unsigned int size, bool dynamic){
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer->m_RendererID));
    if (dynamic){
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    } else{
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }
}

void destroyVertexBuffer(VertexBuffer *buffer){
    GLCall(glDeleteBuffers(1, &(buffer->m_RendererID)));
}

void bindVertexBuffer(VertexBuffer *buffer){
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer->m_RendererID));
}

void unbindVertexBuffer(VertexBuffer *buffer){
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

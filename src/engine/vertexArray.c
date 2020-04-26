#include "vertexArray.h"

#include "utils.h"

void initializeVertexArray(VertexArray *va){
    GLCall(glGenVertexArrays(1, &(va->m_RendererID)));
}

void destroyVertexArray(VertexArray *va){
    GLCall(glDeleteVertexArrays(1, &(va->m_RendererID)));
}

void bindVertexArray(VertexArray *va){
    GLCall(glBindVertexArray(va->m_RendererID));
}
void unbindVertexArray(VertexArray *va){
    GLCall(glBindVertexArray(0));
}

void addBufferToVertexArray(VertexArray *va, const VertexBuffer *vb, const VertexBufferLayout *layout){
    bindVertexArray(va);
    bindVertexBuffer(vb);
    unsigned int offset = 0;
    for (unsigned int i = 0; i < layout->numberElements; i++){
        const VertexBufferElement element = layout->m_Elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout->m_Stride, (const void *)offset));
        offset += element.count * getSizeOfType(element.type);
    }
}

void initializeVertexBufferLayout(VertexBufferLayout *layout){
    layout->numberElements = 0;
    layout->m_Stride = 0;
    layout->m_Elements = malloc(sizeof(VertexBufferElement));
}

void destroyVertexBufferLayout(VertexBufferLayout *layout){
    free(layout->m_Elements);
}

void pushElementToVertexBufferLayout(VertexBufferLayout *layout, unsigned int _type, unsigned int _count, char _normalized){
    layout->numberElements++;
    layout->m_Elements = realloc(layout->m_Elements, layout->numberElements * sizeof(VertexBufferElement));
    layout->m_Elements[layout->numberElements - 1].type = _type;
    layout->m_Elements[layout->numberElements - 1].count = _count;
    layout->m_Elements[layout->numberElements - 1].normalized = _normalized;
    layout->m_Stride += _count * getSizeOfType(_type);
}

unsigned int getSizeOfType(unsigned int type){
    if (type == GL_FLOAT){
        return 4;
    } else if (type == GL_UNSIGNED_INT || type == GL_INT){
        return 4;
    } else if (type == GL_UNSIGNED_BYTE){
        return 1;
    } else {
        return -1;
    }
}

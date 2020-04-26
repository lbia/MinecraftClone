#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

typedef struct{

    unsigned int m_RendererID;
    char *m_FilePath;
    unsigned char *m_LocalBuffer;

    int m_Width, m_Height, m_BPP;

} Texture;

typedef struct{

    Texture top;
    Texture side;
    Texture bottom;

} BlockTexture;

void initializeTexture(Texture *texture, const char *path);

void destroyTexture(Texture *texture);

void bindTexture(Texture *texture, unsigned int slot);

void unbindTexture(Texture *texture);

void bindBlockTexture(BlockTexture *blockTexture, int texture);

BlockTexture *createBlockTexture();

#endif // TEXTURE_H_INCLUDED

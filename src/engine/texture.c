#include "texture.h"

#include "stb_image.h"
#include "utils.h"

void initializeTexture(Texture *texture, const char *path){
    texture->m_RendererID = 0;
    texture->m_FilePath = path;
    texture->m_LocalBuffer = NULL;
    texture->m_Width = 0;
    texture->m_Height = 0;
    texture->m_BPP = 0;

    stbi_set_flip_vertically_on_load(1);
    texture->m_LocalBuffer = stbi_load(texture->m_FilePath, &(texture->m_Width), &(texture->m_Height), &(texture->m_BPP), 4);

    //printf("width %d height %d\n", texture->m_Width, texture->m_Height);

    GLCall(glGenTextures(1, &(texture->m_RendererID)));
    GLCall(glBindTexture(GL_TEXTURE_2D, texture->m_RendererID));

    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    //GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    /*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->m_Width, texture->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->m_LocalBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);*/

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->m_Width, texture->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->m_LocalBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (texture->m_LocalBuffer){
        stbi_image_free(texture->m_LocalBuffer);
    }
}

void destroyTexture(Texture *texture){
    GLCall(glDeleteTextures(1, texture->m_RendererID));
}

void bindTexture(Texture *texture, unsigned int slot){
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, texture->m_RendererID));
}

void unbindTexture(Texture *texture){
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void bindBlockTexture(BlockTexture *blockTexture, int texture){
    bindTexture(&(blockTexture[texture].top), 0);
    bindTexture(&(blockTexture[texture].side), 1);
    bindTexture(&(blockTexture[texture].bottom), 2);
}

Texture **createMobTexture(){
    Texture **mobTextures = (Texture **)malloc(sizeof(Texture *) * NUMERO_MOB_TEXTURES);
    mobTextures[MOB_ZOMBIE] = malloc(sizeof(Texture));
    initializeTexture(mobTextures[MOB_ZOMBIE], "res/mob/zombie.png");
    return mobTextures;
}

BlockTexture *createBlockTexture(){
    BlockTexture *blockTextures = malloc(sizeof(BlockTexture) * NUMERO_TEXTURES);
    initializeTexture(&(blockTextures[TEX_GRASS].top), "res/blocks/grassTop.png");
    initializeTexture(&(blockTextures[TEX_GRASS].side), "res/blocks/grass_side.png");
    initializeTexture(&(blockTextures[TEX_GRASS].bottom), "res/blocks/dirt.png");
    initializeTexture(&(blockTextures[TEX_COBBLESTONE].top), "res/blocks/cobblestone.png");
    initializeTexture(&(blockTextures[TEX_COBBLESTONE].side), "res/blocks/cobblestone.png");
    initializeTexture(&(blockTextures[TEX_COBBLESTONE].bottom), "res/blocks/cobblestone.png");
    initializeTexture(&(blockTextures[TEX_SAND].top), "res/blocks/sand.png");
    initializeTexture(&(blockTextures[TEX_SAND].side), "res/blocks/sand.png");
    initializeTexture(&(blockTextures[TEX_SAND].bottom), "res/blocks/sand.png");
    initializeTexture(&(blockTextures[TEX_WOOD].top), "res/blocks/tree_top.png");
    initializeTexture(&(blockTextures[TEX_WOOD].side), "res/blocks/tree_side.png");
    initializeTexture(&(blockTextures[TEX_WOOD].bottom), "res/blocks/tree_top.png");
    initializeTexture(&(blockTextures[TEX_DIRT].top), "res/blocks/dirt.png");
    initializeTexture(&(blockTextures[TEX_DIRT].side), "res/blocks/dirt.png");
    initializeTexture(&(blockTextures[TEX_DIRT].bottom), "res/blocks/dirt.png");
    initializeTexture(&(blockTextures[TEX_STONE].top), "res/blocks/stone.png");
    initializeTexture(&(blockTextures[TEX_STONE].side), "res/blocks/stone.png");
    initializeTexture(&(blockTextures[TEX_STONE].bottom), "res/blocks/stone.png");
    /*initializeTexture(&(blockTextures[TEX_LEAVES].top), "res/blocks/leaves.png");
    initializeTexture(&(blockTextures[TEX_LEAVES].side), "res/blocks/leaves.png");
    initializeTexture(&(blockTextures[TEX_LEAVES].bottom), "res/blocks/leaves.png");*/
    initializeTexture(&(blockTextures[TEX_LEAVES].top), "res/textures/leaves.png");
    initializeTexture(&(blockTextures[TEX_LEAVES].side), "res/textures/leaves.png");
    initializeTexture(&(blockTextures[TEX_LEAVES].bottom), "res/textures/leaves.png");
    initializeTexture(&(blockTextures[TEX_SNOW].top), "res/blocks/snow.png");
    initializeTexture(&(blockTextures[TEX_SNOW].side), "res/blocks/snow_side.png");
    initializeTexture(&(blockTextures[TEX_SNOW].bottom), "res/blocks/dirt.png");
    initializeTexture(&(blockTextures[TEX_BIRCH].top), "res/blocks/birch_log_top.png");
    initializeTexture(&(blockTextures[TEX_BIRCH].side), "res/blocks/birch_log.png");
    initializeTexture(&(blockTextures[TEX_BIRCH].bottom), "res/blocks/birch_log_top.png");
    initializeTexture(&(blockTextures[TEX_SLIME].top), "res/textures/slimeFaccia.jpeg");
    initializeTexture(&(blockTextures[TEX_SLIME].side), "res/textures/slimeSide.png");
    initializeTexture(&(blockTextures[TEX_SLIME].bottom), "res/textures/slimeSide.png");
    initializeTexture(&(blockTextures[TEX_WATER].top), "res/blocks/water.png");
    initializeTexture(&(blockTextures[TEX_WATER].side), "res/blocks/water.png");
    initializeTexture(&(blockTextures[TEX_WATER].bottom), "res/blocks/water.png");
    return blockTextures;
}

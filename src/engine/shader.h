#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include "cglm/cglm.h"

/* ricordarsi che sono in ordine alfabetico */
#define VIEW_LOCATION       5

typedef struct{
    const char *vertexShader;
    const char *fragmentShader;
} ShaderProgramSource;

typedef struct{

    //TODO: aggiungere unordered map per non cercare ogni volta nome
    const char *m_FilePath;
    unsigned int m_RendererID;

} Shader;

void initializeShaderOnePath(Shader *shader, const char *filePath);

void initializeShaderTwoPaths(Shader *shader, const char *vertexPath, const char *fragmentPath);

void destoyShader(Shader *shader);

void bindShader(Shader *shader);

void unbindShader(Shader *shader);

void setShaderUniform1i(Shader *shader, const char *name, int value);

void setShaderUniform1f(Shader *shader, const char *name, float value);

void setShaderUniformVec3(Shader *shader, const char *name, float v[3]);

void setShaderUniformVec4(Shader *shader, const char *name, float v[4]);

void setShaderUniform4f(Shader *shader, const char *name, float v0, float v1, float v2, float v3);

void setShaderUniformMat4f(Shader *shader, const char *name, const mat4 *mat);

int getShaderUniformLocation(Shader *shader, const char *name);

unsigned int createShader(const char *vertexShader, const char *fragmentShader);

unsigned int compileShader(unsigned int type, const char *source);

ShaderProgramSource parseShaderFromOnePath(const char *filePath);

ShaderProgramSource parseShaderFromTwoPaths(const char *vertexPath, const char *fragmentPath);

char *loadFileToString(const char *path);

#endif // SHADER_H_INCLUDED

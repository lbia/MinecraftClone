#include "shader.h"

#include "utils.h"

#include <stdio.h>

void initializeShaderOnePath(Shader *shader, const char *filePath){
    ShaderProgramSource source = parseShaderFromOnePath(filePath);
    shader->m_FilePath = filePath;
    shader->m_RendererID = createShader(source.vertexShader, source.fragmentShader);
}

void initializeShaderTwoPaths(Shader *shader, const char *vertexPath, const char *fragmentPath){
    ShaderProgramSource source = parseShaderFromTwoPaths(vertexPath, fragmentPath);
    shader->m_FilePath = "usati due path";
    shader->m_RendererID = createShader(source.vertexShader, source.fragmentShader);
}

void destoyShader(Shader *shader){
    GLCall(glDeleteProgram(shader->m_RendererID));
}

void bindShader(Shader *shader){
    GLCall(glUseProgram(shader->m_RendererID));
}

void unbindShader(Shader *shader){
    GLCall(glUseProgram(0));
}

void setShaderUniform1i(Shader *shader, const char *name, int value){
    GLCall(glUniform1i(getShaderUniformLocation(shader, name), value));
}

void setShaderUniform1f(Shader *shader, const char *name, float value){
    GLCall(glUniform1f(getShaderUniformLocation(shader, name), value));
}

void setShaderUniformVec3(Shader *shader, const char *name, float v[3]){
    GLCall(glUniform3f(getShaderUniformLocation(shader, name), v[0], v[1], v[2]));
}

void setShaderUniformVec4(Shader *shader, const char *name, float v[4]){
    GLCall(glUniform4f(getShaderUniformLocation(shader, name), v[0], v[1], v[2], v[3]));
}

void setShaderUniform4f(Shader *shader, const char *name, float v0, float v1, float v2, float v3){
    GLCall(glUniform4f(getShaderUniformLocation(shader, name), v0, v1, v2, v3));
}

void setShaderUniformMat4f(Shader *shader, const char *name, const mat4 *mat){
    GLCall(glUniformMatrix4fv(getShaderUniformLocation(shader, name), 1, GL_FALSE, mat));
}

int getShaderUniformLocation(Shader *shader, const char *name){
    //TODO: aggiungere unordered map per non cercare ogni volta il nome
    GLCall(int location = glGetUniformLocation(shader->m_RendererID, name));
    if (location == -1){
        printf("ATTENTION: uniform %s doesn't exist\n", name);
    }
    return location;
}

unsigned int createShader(const char *vertexShader, const char *fragmentShader){
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //link to one program
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int compileShader(unsigned int type, const char *source){
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    //error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    char *nomeShader;
    if (type == GL_VERTEX_SHADER){
        nomeShader = "Vertex Shader";
    } else if (type == GL_FRAGMENT_SHADER){
        nomeShader = "Fragment Shader";
    }
    if (result == GL_FALSE){
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char *message = (char *)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        printf("ERROR: problemi nel compilamento di %s\n", nomeShader);
        printf("%s\n", message);
        glDeleteShader(id);
        return 0;
    } else {
        //printf("%s compilato correttamente\n", nomeShader);
    }
    return id;
}

ShaderProgramSource parseShaderFromOnePath(const char *filePath){
    printf("Leggendo 1 path\n");
    char *vs = (char *)calloc(1, sizeof(char));
    char *fs = (char *)calloc(1, sizeof(char));
    int posvs = 0;
    int posfs = 0;
    char carattere;
    int situazione = 0;                 //0 nulla 1 vertex 2 fragment
    FILE *file = fopen(filePath, "r");

    fscanf(file, "%c", &carattere);
    while(!feof(file)){
            printf("%c", carattere);
        if (carattere == '£'){
            char c1, c2, c3;
            fscanf(file, "%c", &c1);
            fscanf(file, "%c", &c2);
            fscanf(file, "%c", &c3);
            if (c1 == 'v' && c2 == 'e' && c3 == 'r'){
                situazione = 1;
            } else if (c1 == 'f' && c2 == 'r' && c3 == 'a'){
                situazione = 2;
            } else {
                printf("ERROR: nel cambio di shader\n");
            }
            fscanf(file, "%c", &carattere);
        }
        if (situazione == 1){
            posvs++;
            vs = (char *)realloc(vs, sizeof(char) * (posvs));
            vs[posvs - 1] = carattere;
        } else if (situazione == 2){
            posfs++;
            fs = (char *)realloc(fs, sizeof(char) * (posfs));
            fs[posfs - 1] = carattere;
        }
        fscanf(file, "%c", &carattere);
    }
    vs[posvs - 1] = '\0';
    fs[posfs - 1] = '\0';
    printf("Vertex Shader: %s\n", vs);
    printf("Fragment Shader: %s\n", fs);

    fclose(file);

    ShaderProgramSource fine;
    fine.vertexShader = vs;
    fine.fragmentShader = fs;

    return fine;
}

ShaderProgramSource parseShaderFromTwoPaths(const char *vertexPath, const char *fragmentPath){
    char *vs = loadFileToString(vertexPath);
    char *fs = loadFileToString(fragmentPath);
    ShaderProgramSource fine;
    fine.vertexShader = vs;
    fine.fragmentShader = fs;

    return fine;
}

char *loadFileToString(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        printf("Problemi nell'aprire %s\n", path);
    }
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    rewind(file);
    char *data = calloc(length + 1, sizeof(char));
    fread(data, 1, length, file);
    fclose(file);
    return data;
}

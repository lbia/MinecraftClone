#include "window.h"

GLFWwindow *initializeWindow(const char *name, GameState *state, bool cursoreFisso){
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit()){
        exit(-1);
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, name, NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(-1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //constant frame rate
    glfwSwapInterval(1);

    //add gameState to window user pointer
    glfwSetWindowUserPointer(window, state);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    if (cursoreFisso){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    if (glewInit() != GLEW_OK){
        printf("ERRORE di caricamento di Glew\n");
    }
    //enabling blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LESS));

    GLCall(glClearColor(CLEAR_COLOR));
    //GLCall(glClearColor(25 / coverter, 181 / coverter, 254 / coverter, 1.0f));
    //GLCall(glClearColor(23 / coverter, 191 / coverter, 241 / coverter, 1.0f));
    //GLCall(glClearColor(255 / coverter, 255 / coverter, 255 / coverter, 1.0f));

    //per versione OpenGL
    printf("VERSION: %s\n", glGetString(GL_VERSION));

    // Returns the vendor
    const char* vendor = glGetString(GL_VENDOR);
    // Returns a hint to the model
    const char* model = glGetString(GL_RENDERER);

    printf("VENDOR: %s\n", vendor);
    printf("MODEL: %s\n", model);

    return window;
}

void processInput(GLFWwindow *window){
    GameState *state = (GameState *)glfwGetWindowUserPointer(window);
    Player *player = state->player;
    /*float currentFrame = glfwGetTime();
    state->deltaTime = currentFrame - state->lastFrame;
    state->lastFrame = currentFrame;*/
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        state->spazioPremuto = true;
        if (!player->jump){
            startJump(player, JUMP_VEL, player->camera->position[1]);
        }
    } else{
        state->spazioPremuto = false;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS){
        state->scendiPremuto = true;
    } else{
        state->scendiPremuto = false;
    }
    player->camera->movementSpeed = SPEED_DEFAULT;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && player->jump == false && state->creative == false){
        player->shift = true;
        player->camera->movementSpeed = SPEED_SHIFT;
    } else{
        player->shift = false;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
        player->camera->movementSpeed = SPEED_SCATTO;
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        state->textureSelezionata = TEX_GRASS;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        state->textureSelezionata = TEX_SAND;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
        state->textureSelezionata = TEX_COBBLESTONE;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS){
        state->textureSelezionata = TEX_WOOD;
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS){
        state->textureSelezionata = TEX_STONE;
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS){
        state->textureSelezionata = TEX_LEAVES;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
        state->textureSelezionata = PIANTA_ALBERO;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && state->creative == false){
        state->creative = true;
        endJump(state->player, state->player->camera->position[1]);
        state->player->camera->movementSpeed = SPEED_CREATIVE;
        printf("creative\n");
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && state->creative == true){
        state->creative = false;
        startJump(state->player, 0, state->player->camera->position[1]);
        printf("survival\n");
    }
    if (state->creative){
        state->player->camera->movementSpeed = SPEED_CREATIVE;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        getUpdateCameraPosition(player->camera, 0, state->deltaTime, player->newPositionCamera);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        getUpdateCameraPosition(player->camera, 1, state->deltaTime, player->newPositionCamera);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        getUpdateCameraPosition(player->camera, 2, state->deltaTime, player->newPositionCamera);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        getUpdateCameraPosition(player->camera, 3, state->deltaTime, player->newPositionCamera);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && !state->rightPress){
        state->rightPress = true;
        piazzaBlocco(state, state->textureSelezionata);
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE && state->rightPress){
        state->rightPress = false;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS && !state->leftPress){
        state->leftPress = true;
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE && state->leftPress){
        state->leftPress = false;
        player->timeRotturaBlocco = 0;
        player->bloccoDaRompere[0] = -1;
        player->bloccoDaRompere[1] = -1;
        player->bloccoDaRompere[2] = -1;
    }
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos){
    GameState *state = (GameState *)glfwGetWindowUserPointer(window);

    if(state->firstMouse){
        state->lastX = xPos;
        state->lastY = yPos;
        state->firstMouse = false;
    }

    float xOffset = xPos - state->lastX;
    float yOffset = yPos - state->lastY;

    state->lastX = xPos;
    state->lastY = yPos;

    processCameraMouseMovement(state->player->camera, xOffset, yOffset, true);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset){
    GameState *state = (GameState *)glfwGetWindowUserPointer(window);
    //processCameraMouseScroll(state->player->camera, yOffset);
    processMouseScroll(state, yOffset);
}

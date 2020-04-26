#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "renderer.h"
#include "gameState.h"

GLFWwindow *initializeWindow(const char *name, GameState *state, bool cursoreFisso);

void processInput(GLFWwindow *window);

void mouseCallback(GLFWwindow* window, double xPos, double yPos);

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

#endif // WINDOW_H_INCLUDED

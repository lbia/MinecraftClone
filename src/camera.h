#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "cglm/cglm.h"
#include "stdbool.h"

#define YAW_DEFAULT -90.0
#define PITCH_DEFAULT 0.0
#define SPEED_DEFAULT 3
#define SPEED_SCATTO 5
#define SPEED_SHIFT 1
#define SPEED_CREATIVE 30
#define SENSITIVITY_DEFAULT 0.1
#define ZOOM_DEFAULT 45.0

typedef struct{

    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

} Camera;

void initializeCameraVector(Camera *camera, vec3 pos, vec3 up, float yaw, float pitch);

void initializeCameraScalar(Camera *camera, float x, float y, float z);

void processCameraKeyBoard(Camera *camera, int direction, float deltaTime);

void processCameraMouseMovement(Camera *camera, float xOffset, float yOffset, bool constrainPitch);

void getUpdateCameraPosition(Camera *camera, int direction, float deltaTime, vec2 dest);

void setCameraPositionXZ(Camera *camera, vec2 newPosition);

void processCameraMouseScroll(Camera *camera, float yOffset);

void getCameraViewMatrix(Camera *camera, bool shift, mat4 mat);

float *getCameraDavanti2d(Camera *camera);

#endif // CAMERA_H_INCLUDED

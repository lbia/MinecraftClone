#include "camera.h"

#include <math.h>

void updateCameraVectors(Camera *camera){
    // Calculate the new Front vector
    vec3 front, right, up;
    front[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    front[1] = -sin(glm_rad(camera->pitch));
    front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    glm_normalize(front);

    // Also re-calculate the Right and Up vector
    glm_cross(front, camera->worldUp, right);
    glm_normalize(right);
    // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    glm_cross(right, front, up);
    glm_normalize(up);

    glm_vec3_copy(front, camera->front);
    glm_vec3_copy(right, camera->right);
    glm_vec3_copy(up, camera->up);
}

void initializeCameraVector(Camera *camera, vec3 pos, vec3 up, float yaw, float pitch){
    glm_vec3_copy(pos, camera->position);
    glm_vec3_copy(up, camera->worldUp);
    camera->yaw = yaw;
    camera->pitch = pitch;

    camera->movementSpeed = SPEED_DEFAULT;
    camera->mouseSensitivity = SENSITIVITY_DEFAULT;
    camera->zoom = ZOOM_DEFAULT;

    updateCameraVectors(camera);
}

void initializeCameraScalar(Camera *camera, float x, float y, float z){
    vec3 pos = {x, y, z};
    vec3 up = {0, 1, 0};
    glm_vec3_copy(pos, camera->position);
    glm_vec3_copy(up, camera->worldUp);

    camera->yaw = YAW_DEFAULT;
    camera->pitch = PITCH_DEFAULT;
    camera->movementSpeed = SPEED_DEFAULT;
    camera->mouseSensitivity = SENSITIVITY_DEFAULT;
    camera->zoom = ZOOM_DEFAULT;

    updateCameraVectors(camera);
}

void getCameraViewMatrix(Camera *camera, bool shift, mat4 mat){
    glm_mat4_identity(mat);
    vec3 pos;
    if (!shift){
        pos[0] = camera->position[0];
        pos[1] = camera->position[1];
        pos[2] = camera->position[2];
    } else {
        pos[0] = camera->position[0];
        pos[1] = camera->position[1] - 0.2;
        pos[2] = camera->position[2];
    }
    vec3 center;
    glm_vec3_add(pos, camera->front, center);
    glm_lookat(pos, center, camera->up, mat);
}

void setCameraPositionXYZ(Camera *camera, vec3 newPosition){
    camera->position[0] = newPosition[0];
    camera->position[1] = newPosition[1];
    camera->position[2] = newPosition[2];
}

void setCameraPositionXZ(Camera *camera, vec2 newPosition){
    camera->position[0] = newPosition[0];
    camera->position[2] = newPosition[1];
}

float *getCameraDavanti2d(Camera *camera){
    vec3 davanti;
    davanti[0] = camera->front[0];
    davanti[1] = 0;
    davanti[2] = camera->front[2];
    glm_vec3_normalize(davanti);
    float *fine = malloc(sizeof(float) * 2);
    fine[0] = davanti[0];
    fine[1] = davanti[2];
    return fine;
}

void getUpdateCameraPosition(Camera *camera, int direction, float deltaTime, vec2 dest){
    float vel = camera->movementSpeed * deltaTime;
    vec3 davanti, destra;
    davanti[0] = camera->front[0];
    davanti[1] = 0;
    davanti[2] = camera->front[2];
    glm_vec3_normalize(davanti);
    glm_vec3_copy(camera->right, destra);
    vec2 newPosition;
    if (direction == 0){
        newPosition[0] = camera->position[0] + davanti[0] * vel;
        newPosition[1] = camera->position[2] + davanti[2] * vel;
    } else if (direction == 1){
        newPosition[0] = camera->position[0] - davanti[0] * vel;
        newPosition[1] = camera->position[2] - davanti[2] * vel;
    } else if (direction == 2){
        newPosition[0] = camera->position[0] - destra[0] * vel;
        newPosition[1] = camera->position[2] - destra[2] * vel;
    } else if (direction == 3){
        newPosition[0] = camera->position[0] + destra[0] * vel;
        newPosition[1] = camera->position[2] + destra[2] * vel;
    }
    dest[0] = newPosition[0];
    dest[1] = newPosition[1];
}

void processCameraMouseMovement(Camera *camera, float xOffset, float yOffset, bool constrainPitch){
    xOffset *= camera->mouseSensitivity;
    yOffset *= camera->mouseSensitivity;

    camera->yaw += xOffset;
    camera->pitch += yOffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch){
        if (camera->pitch > 89.0f){
            camera->pitch = 89.0f;
        } else if (camera->pitch < -89.0f)
            camera->pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors(camera);
}

void processCameraMouseScroll(Camera *camera, float yOffset){
    if (camera->zoom >= 1.0f && camera->zoom <= 45.0f){
        camera->zoom -= yOffset;
    } else if (camera->zoom <= 1.0f){
        camera->zoom = 1.0f;
    } else if (camera->zoom >= 45.0f){
        camera->zoom = 45.0f;
    }
}

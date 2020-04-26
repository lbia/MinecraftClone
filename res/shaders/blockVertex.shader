#version 460

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texIndex;
layout(location = 3) in vec3 normal;

out vec2 v_TexCoord;
out float v_TexIndex;
out vec3 v_SurfaceNormal;
out vec3 v_ToLightVector;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;
uniform vec3 u_LightPosition;

void main(){
    vec4 worldPosition = u_Model * vec4(position, 1.0);
    gl_Position = u_Proj * u_View * worldPosition;
    v_TexCoord = texCoord;
    v_TexIndex = texIndex;

    v_SurfaceNormal = normalize((u_Model * vec4(normal, 0.0)).xyz);
    v_ToLightVector = normalize(u_LightPosition - worldPosition.xyz);
}

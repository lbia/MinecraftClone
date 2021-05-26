#version 460

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;
in vec3 v_SurfaceNormal;
in vec3 v_ToLightVector;

uniform sampler2D u_BlockTop;
uniform sampler2D u_BlockSide;
uniform sampler2D u_BlockBottom;
uniform vec4 u_TexColor;
uniform vec3 u_LightColor;

void main(){
    vec4 texColor;
    if (v_TexIndex < 0.1f){
        texColor = texture(u_BlockTop, v_TexCoord);
    } else if (v_TexIndex < 1.1f){
        texColor = texture(u_BlockSide, v_TexCoord);
    } else if (v_TexIndex < 2.1f){
        texColor = texture(u_BlockBottom, v_TexCoord);
    }
    float dot1 = ((dot(v_SurfaceNormal, v_ToLightVector) + 1) / 2.0) * 1.2;
    float brightness = max(dot1, 0.4);
    vec3 diffuse = brightness * u_LightColor;
	//color = u_TexColor * vec4(diffuse, 1.0) * texColor;
	color = vec4(diffuse, 1.0) * texColor;
}

#version 460

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_MouseBianco;

void main(){
    vec4 texColor;
    texColor = texture(u_MouseBianco, v_TexCoord);
    float threshold = 0.99f;
    if (texColor.r > threshold && texColor.g > threshold && texColor.b > threshold){
        texColor.a = 1.0f;
    }
    threshold = 0.01f;
    if (texColor.r < threshold && texColor.g < threshold && texColor.b < threshold){
        discard;
    }
	color = texColor;
}

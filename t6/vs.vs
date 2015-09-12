#version 330

layout (location = 0) in vec3 vPosition;

uniform mat4 gWorld;

void main(){
    gl_Position = gWorld * vec4(vPosition,1.0f);
}
#version 330

layout (location = 0) in vec3 vPosition;

uniform float gScale;

void main(){
    gl_Position = vec4(gScale * vPosition.x,gScale * vPosition.y,vPosition.z,1.0);
}